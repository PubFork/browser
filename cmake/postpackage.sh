#!/bin/bash
set -e

cd dist

shopt -s nullglob
for tgz in axr-browser-*-OPERATING_SYSTEM-*.tar.gz
do
    os=$(uname | awk '{print tolower($0)}')
    tgz2=${tgz/OPERATING_SYSTEM/$os}
    mv "$tgz" "$tgz2"

    # We don't want "OPERATING_SYSTEM" showing up...
    tar xzf "$tgz2"
    mv "${tgz%.tar.gz}" "${tgz2%.tar.gz}"
    rm "$tgz2"
    tar czf "$tgz2" "${tgz2%.tar.gz}"
    rm -r "${tgz2%.tar.gz}"
done

if [ -f $pkgfilename-browser.deb ] ; then
    # Fix package name
    mv $pkgfilename-browser.deb $pkgfilename.deb

    # Deconstruct .deb
    rm -rf $pkgfilename.tmp
    dpkg-deb --raw-extract $pkgfilename.deb $pkgfilename.tmp
    rm $pkgfilename.deb

    # Set permissions correctly since CPack doesn't do it...
    cd $pkgfilename.tmp

    fakeroot chmod 0644 DEBIAN/*
    fakeroot find usr -type d | xargs chmod 0755
    fakeroot chown -R root:root *

    cd ..

    # Repackage
    fakeroot dpkg --build $pkgfilename.tmp $pkgfilename.deb
    rm -rf $pkgfilename.tmp

    # Check the .deb file for problems
    lintian $pkgfilename.deb
elif [ -f $pkgfilename-browser.rpm ] ; then
    # Fix package name
    mv $pkgfilename-browser.rpm $pkgfilename.rpm
fi
