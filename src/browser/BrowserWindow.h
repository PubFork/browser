/********************************************************************
 *             a  A
 *            AM\/MA
 *           (MA:MMD
 *            :: VD
 *           ::  º
 *          ::
 *         ::   **      .A$MMMMND   AMMMD     AMMM6    MMMM  MMMM6
 +       6::Z. TMMM    MMMMMMMMMDA   VMMMD   AMMM6     MMMMMMMMM6
 *      6M:AMMJMMOD     V     MMMA    VMMMD AMMM6      MMMMMMM6
 *      ::  TMMTMC         ___MMMM     VMMMMMMM6       MMMM
 *     MMM  TMMMTTM,     AMMMMMMMM      VMMMMM6        MMMM
 *    :: MM TMMTMMMD    MMMMMMMMMM       MMMMMM        MMMM
 *   ::   MMMTTMMM6    MMMMMMMMMMM      AMMMMMMD       MMMM
 *  :.     MMMMMM6    MMMM    MMMM     AMMMMMMMMD      MMMM
 *         TTMMT      MMMM    MMMM    AMMM6  MMMMD     MMMM
 *        TMMMM8       MMMMMMMMMMM   AMMM6    MMMMD    MMMM
 *       TMMMMMM$       MMMM6 MMMM  AMMM6      MMMMD   MMMM
 *      TMMM MMMM
 *     TMMM  .MMM
 *     TMM   .MMD       ARBITRARY·······XML········RENDERING
 *     TMM    MMA       ====================================
 *     TMN    MM
 *      MN    ZM
 *            MM,
 *
 *
 *      AUTHORS: see AUTHORS file
 *
 *      COPYRIGHT: ©2013 - All Rights Reserved
 *
 *      LICENSE: see LICENSE file
 *
 *      WEB: http://axrproject.org
 *
 *      THIS CODE AND INFORMATION ARE PROVIDED "AS IS"
 *      WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
 *      OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *      IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
 *      FITNESS FOR A PARTICULAR PURPOSE.
 *
 ********************************************************************/

#ifndef AXR_BROWSER_BROWSERWINDOW
#define AXR_BROWSER_BROWSERWINDOW

#include <QMainWindow>

namespace Ui
{
    class BrowserWindow;
}

class BrowserTab;
class QUrl;

class BrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    BrowserWindow(QWidget *parent = NULL);
    virtual ~BrowserWindow();

public:
    BrowserTab* currentTab() const;
    QList<BrowserTab*> tabs() const;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    bool event(QEvent *);

public slots:
    int newTab();
    void openFile();
    void openAddressBarUrl();
    void openUrl(const QUrl &url, bool newTab = true);
    void openUrls(const QList<QUrl> &urls, bool newTab = true);
    void openFile(const QString &filePath, bool newTab = true);
    void openFiles(const QStringList &filePaths, bool newTab = true);
    void reloadFile();
    void closeCurrentTab();
    void closeTab(int index);

    void previousLayoutStep();
    void nextLayoutStep();

    void showErrorLog();
    void showPreferences();
    void showAbout();

    void toggleAntialiasing(bool on);

private slots:
    void updateUIForCurrentTabState();

private:
    class Private;
    Private *d;
    Ui::BrowserWindow *ui;
};

#endif
