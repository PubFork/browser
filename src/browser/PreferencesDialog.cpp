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

#include <QAction>
#include <QDesktopWidget>
#include <QIcon>
#include <QSettings>
#include <QToolBar>
#include "PreferencesDialog.h"
#include "BrowserApplication.h"
#include "BrowserSettings.h"
#include "ui_PreferencesDialog.h"
#include "qtmacunifiedtoolbar.h"

class PreferencesDialog::Private
{
public:
    Private() : pageActionsGroup(NULL), finishedLoading(false) { }

    QActionGroup *pageActionsGroup;
    bool finishedLoading;
};

PreferencesDialog::PreferencesDialog(QWidget *parent)
: QMainWindow(parent), d(new Private), ui(new Ui::PreferencesDialog)
{
    this->ui->setupUi(this);

    d->pageActionsGroup = new QActionGroup(this);

    // Icons from /System/Library/CoreServices/CoreTypes.bundle/Contents
    d->pageActionsGroup->addAction(ui->generalAction); // General.icns
    d->pageActionsGroup->addAction(ui->debugAction); // KEXT.icns

    loadPreferences();
    switchPage();

#ifdef Q_OS_MAC
    this->setWindowModality(Qt::NonModal);
    this->ui->buttonBox->hide();

    ::setUnifiedTitleAndToolBarOnMac(ui->toolBar);

    // OS X seems to prefer settings dialogs to be placed at (<center>, 150)
    this->adjustSize();
    this->move((qApp->desktop()->width() - this->width()) / 2, 150);
#endif
}

PreferencesDialog::~PreferencesDialog()
{
    delete d;
    delete this->ui;
}

void PreferencesDialog::loadPreferences()
{
    ui->fileLaunchActionComboBox->setCurrentIndex(qApp->settings()->fileLaunchAction());
    ui->autoReloadCheckBox->setChecked(qApp->settings()->autoReload());
}

void PreferencesDialog::accept()
{
    // Don't save settings until the dialog is fully loaded, otherwise we'll
    // overwrite settings as we're reading them during the loading stage
    if (!d->finishedLoading)
        return;

    qApp->settings()->setFileLaunchAction(static_cast<BrowserSettings::FileLaunchAction>(ui->fileLaunchActionComboBox->currentIndex()));
    qApp->settings()->setAutoReload(ui->autoReloadCheckBox->isChecked());

#ifndef Q_OS_MAC
    close();
#endif
}

void PreferencesDialog::reject()
{
    close();
}

void PreferencesDialog::preferenceChanged()
{
#ifdef Q_OS_MAC
    accept();
#endif
}

void PreferencesDialog::switchPage()
{
    QAction *current = d->pageActionsGroup->checkedAction();
    if (!current)
    {
        current = ui->generalAction;
        current->setChecked(true);
    }

    if (current == ui->generalAction)
        ui->stackedWidget->setCurrentWidget(ui->generalPage);
    else if (current == ui->debugAction)
        ui->stackedWidget->setCurrentWidget(ui->debugPage);

    this->adjustSize();
}
