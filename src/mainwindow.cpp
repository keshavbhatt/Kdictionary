#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cookiejar.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    settings.setObjectName("settings");
    ui->setupUi(this);
    showMsgBox = true;
    QSplitter *split1 = new QSplitter;
    QSplitter *split2 = new QSplitter;

    split1->setObjectName("split1");
    split2->setObjectName("split2");

    split1->setOrientation(Qt::Horizontal);
    split2->setOrientation(Qt::Vertical);

    split2->addWidget(ui->textBrowser);
    split2->addWidget(ui->verticalWidgetOnline);

    split1->addWidget(ui->leftWidget);
    split1->addWidget(ui->verticalWidgetRight);


    ui->horizontalLayout_2->addWidget(split1);
    ui->verticalWidgetRight->layout()->addWidget(split2);

    ui->verticalWidgetRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    btn_style ="QPushButton{color: silver; background-color: #484846; border-width: 1px; border-color: #302F2F; border-style: solid; padding-top: 3px; padding-bottom: 3px; padding-left: 3px; padding-right: 3px; border-radius: 2px; outline: none;}"
   "QPushButton:disabled { background-color: #424242; border-width: 1px; border-color: #302F2F; border-style: solid; padding-top: 3px; padding-bottom: 3px; padding-left: 5px; padding-right: 5px; /*border-radius: 2px;*/ color: #636363;}"
   "QPushButton:focus { background-color: #484846; color: silver;}"
   "QPushButton:hover{border: 1px solid #55554D;background-color:#55554D;color:silver ;}"
   "QPushButton:pressed {background-color: #484846;color: silver;padding-bottom:1px;}";


    init_instant_result();

    db = QSqlDatabase::addDatabase("QSQLITE");

    QString db_path ;

    if(QFileInfo(QFile(QCoreApplication::applicationDirPath()+"/Dictionary.db")).exists()){
        db_path = QCoreApplication::applicationDirPath()+"/Dictionary.db";
    }else{
        db_path = "/usr/bin/Dictionary.db";
    }
    db.setDatabaseName(db_path);
    db.open();

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    setStyle(":/style.qss");

    ui->lineEdit->setText("Welcome");

    if(ui->wordnetSearchBtn->isEnabled())
    on_wordnetSearchBtn_clicked();

    QString btn_style_2=" QPushButton{background-color:transparent ;}"
                         "QPushButton:pressed {padding-bottom:1px;background-color:transparent}"
                         "QPushButton:hover {border:none;padding-bottom:1px;background-color:transparent}";
    ui->close_btn->setStyleSheet(btn_style_2);
    ui->min_btn->setStyleSheet(btn_style_2);
    ui->max_btn->setStyleSheet(btn_style_2);


    ui->textBrowser->setStyleSheet("border-image: url(:/img/img/mainfeatures.png) 0 0 0 0 stretch stretch;");


    QStringList lang;
    lang << "en  English" << "aa  Afar" << "ab  Abkhazian" << "af  Afrikaans" << "am  Amharic" << "ar  Arabic" << "as  Assamese" << "ay  Aymara" << "az  Azerbaijani" << "ba  Bashkir" << "be  Byelorussian" << "bg  Bulgarian" << "bh  Bihari" << "bi  Bislama" << "bn  Bengali/Bangla" << "bo  Tibetan" << "br  Breton" << "ca  Catalan" << "co  Corsican" << "cs  Czech" << "cy  Welsh" << "da  Danish" << "de  German" << "dz  Bhutani" << "el  Greek" << "eo  Esperanto" << "es  Spanish" << "et  Estonian" << "eu  Basque" << "fa  Persian" << "fi  Finnish" << "fj  Fiji" << "fo  Faeroese" << "fr  French" << "fy  Frisian" << "ga  Irish" << "gd  Scots/Gaelic" << "gl  Galician" << "gn  Guarani" << "gu  Gujarati" << "ha  Hausa" << "hi  Hindi" << "hr  Croatian" << "hu  Hungarian" << "hy  Armenian" << "ia  Interlingua" << "ie  Interlingue" << "ik  Inupiak" << "in  Indonesian" << "is  Icelandic" << "it  Italian" << "iw  Hebrew" << "ja  Japanese" << "ji  Yiddish" << "jw  Javanese" << "ka  Georgian" << "kk  Kazakh" << "kl  Greenlandic" << "km  Cambodian" << "kn  Kannada" << "ko  Korean" << "ks  Kashmiri" << "ku  Kurdish" << "ky  Kirghiz" << "la  Latin" << "ln  Lingala" << "lo  Laothian" << "lt  Lithuanian" << "lv  Latvian/Lettish" << "mg  Malagasy" << "mi  Maori" << "mk  Macedonian" << "ml  Malayalam" << "mn  Mongolian" << "mo  Moldavian" << "mr  Marathi" << "ms  Malay" << "mt  Maltese" << "my  Burmese" << "na  Nauru" << "ne  Nepali" << "nl  Dutch" << "no  Norwegian" << "oc  Occitan" << "om  (Afan)/Oromoor/Oriya" << "pa  Punjabi" << "pl  Polish" << "ps  Pashto/Pushto" << "pt  Portuguese" << "qu  Quechua" << "rm  Rhaeto-Romance" << "rn  Kirundi" << "ro  Romanian" << "ru  Russian" << "rw  Kinyarwanda" << "sa  Sanskrit" << "sd  Sindhi" << "sg  Sangro" << "sh  Serbo-Croatian" << "si  Singhalese" << "sk  Slovak" << "sl  Slovenian" << "sm  Samoan" << "sn  Shona" << "so  Somali" << "sq  Albanian" << "sr  Serbian" << "ss  Siswati" << "st  Sesotho" << "su  Sundanese" << "sv  Swedish" << "sw  Swahili" << "ta  Tamil" << "te  Tegulu" << "tg  Tajik" << "th  Thai" << "ti  Tigrinya" << "tk  Turkmen" << "tl  Tagalog" << "tn  Setswana" << "to  Tonga" << "tr  Turkish" << "ts  Tsonga" << "tt  Tatar" << "tw  Twi" << "uk  Ukrainian" << "ur  Urdu" << "uz  Uzbek" << "vi  Vietnamese" << "vo  Volapuk" << "wo  Wolof" << "xh  Xhosa" << "yo  Yoruba" << "zh  Chinese" << "zu  Zulu";
    for(int i=0; i< lang.count();i++){
        ui->language->addItem(lang.at(i).split("  ").last());
        lang_codes.append(lang.at(i).split("  ").first());
    }

    ui->pronounceWebview->hide();
    ui->pronounceWebview->load(QUrl("qrc:/prnounce/pronounce/index.html"));

    ui->tabWidget->removeTab(1);
    ui->kdictProgressBar->hide();
    ui->wikiProgressBar->hide();
    ui->imageSearchProgressBar->hide();

    connect(ui->language,SIGNAL(currentIndexChanged(int)),this,SLOT(language_changed(int)));

    connect(ui->kdictWebview,SIGNAL(loadProgress(int)),this,SLOT(kdictView_progress(int)));

    connect(ui->kdictWebview,SIGNAL(loadFinished(bool)),this,SLOT(kdictView_loaded(bool)));

    connect(ui->wikipediaWebview,SIGNAL(loadFinished(bool)),this,SLOT(wikiWebView_loaded(bool)));

    connect(ui->wikipediaWebview,SIGNAL(loadProgress(int)),this,SLOT(wikiWebView_progress(int)));

    connect(ui->ImageSearchWebview,SIGNAL(loadProgress(int)),this,SLOT(imageView_progress(int)));

    connect(ui->ImageSearchWebview,SIGNAL(loadFinished(bool)),this,SLOT(show_net_error_message(bool)));

    connect(ui->pronounceWebview,SIGNAL(loadFinished(bool)),this,SLOT(show_net_error_message(bool)));


    dicts<<"*"<<"world02"<<"easton"<<"elements"<<"hitchcock"<<"jargon"<<"gcide"<<"devils"<<"foldoc"<<"gazetteer"<<"vera"<<"wn";

    ui->imageSearchProgressBar->setStyleSheet("QProgressBar::chunk { background-color: #3DAEE9;}QProgressBar { border: 0px solid #76797C; border-radius: 5px; text-align: center;}");

    init_webviews();

    init_main_menu();



    QList<QPushButton*> button_list = this->findChildren<QPushButton *> ();
    for(int i =0; i <button_list.size(); i++)
    {
           button_list.at(i)->setStyleSheet(btn_style);
    }




    nativeHotkey=new QHotkey(this);
    readSettings();
    connect(this->nativeHotkey, &QHotkey::activated,
            this, &MainWindow::get_selected_word_fromX11);


    ui->kdictWebview->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);//important to emit linkClicked signal by webview
    connect(ui->kdictWebview->page(),SIGNAL(linkClicked(QUrl)),this,SLOT(evaluateClickedLink_in_kdictWebPage(QUrl)));



    ui->pronounceWebview->page()->mainFrame()->addToJavaScriptWindowObject("mainWindow", this);

    ui->textBrowser_2->viewport()->installEventFilter(this);
    ui->textBrowser->viewport()->installEventFilter(this);
    ui->wikipediaWebview->installEventFilter(this);
    ui->kdictWebview->installEventFilter(this);
    ui->wordnetTextBrowser->viewport()->installEventFilter(this);

    connect(ui_menu.quickResultCheckBox, &QCheckBox::toggled,
            this->nativeHotkey, &QHotkey::setRegistered);

    connect(ui_menu.keySequenceEdit, &QKeySequenceEdit::keySequenceChanged,
            this, &MainWindow::setShortcut);

    readed_fav = false;
    favLoaded = false;
    hisLoaded = false;
    ui->fakeLineEdit->hide();
    check_fav();

    show_SysTrayIcon();

    if(settings.value("minimize_on_close").toBool()){
            if(!nativeHotkey->isRegistered()){
                QMessageBox msgBox;
                msgBox.setText("<b>Quick Result Error:</b>");
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setInformativeText("Another instance is using "+settings.value("quickdict_shortcut").toString()+" shortcut for Quick result.\n\nQuick Result shortcut not registered and will not work due to multiple instances of application are running.\n\nClose other instances of Application.");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setWindowModality(Qt::ApplicationModal);
                msgBox.setDefaultButton(QMessageBox::Ok);
                int ret= msgBox.exec();
                switch (ret) {
                case QMessageBox::Ok:{
                    QTimer timer;
                    timer.singleShot(200,qApp,SLOT(quit()));
                }
                break;
                default:{
                    this->close();
                    close();
                }
                break;
                }
            }
    }

    connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(close()));
}


void MainWindow::show_SysTrayIcon(){

      QAction *minimizeAction = new QAction(QObject::tr("&Hide"), this);
      this->connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

      QAction *restoreAction = new QAction(QObject::tr("&Restore"), this);
      this->connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

      QAction *quick_result = new QAction(QString("&Quick Result\n("+ui_menu.keySequenceEdit->keySequence().toString()+")"), this);
      quick_result->setCheckable(true);
      quick_result->setChecked(ui_menu.quickResultCheckBox->isChecked());
      connect(quick_result,SIGNAL(toggled(bool)),ui_menu.quickResultCheckBox,SLOT(setChecked(bool)));

      QAction *quitAction = new QAction(QObject::tr("&Quit"), this);
      this->connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

      QMenu *trayIconMenu = new QMenu(this);
      trayIconMenu->addAction(minimizeAction);
      trayIconMenu->addAction(restoreAction);
      trayIconMenu->addSeparator();
      trayIconMenu->addAction(quick_result);
      trayIconMenu->addSeparator();
      trayIconMenu->addAction(quitAction);

      QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
      trayIcon->setContextMenu(trayIconMenu);
      trayIconMenu->setObjectName("trayIconMenu");

      trayIcon->setIcon(QPixmap(":/icons/kdictionary32by32zoomout.png"));
      connect(trayIconMenu,SIGNAL(aboutToShow()),this,SLOT(check_window_state()));
      if(trayIcon->isSystemTrayAvailable()){
          trayIcon->show();
      }
      else{
          QMessageBox msgBox;
          msgBox.setText("<b>System tray:</b>");
          msgBox.setIcon(QMessageBox::Information);
          msgBox.setInformativeText("System tray not found, Please install a system tray in your system.");
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.setDefaultButton(QMessageBox::Ok);
          int ret= msgBox.exec();
          switch (ret) {
          case QMessageBox::Ok:{
             msgBox.close();
          }
              break;
          default:
              break;
          }
      }
}
//check window state and set tray menus
void MainWindow::check_window_state(){

//    qDebug()<<"tray activated";
    QObject *tray_icon_menu = this->findChild<QObject*>("trayIconMenu");
//    qDebug()<<((QMenu*)(tray_icon_menu))->actions().count();
    if(this->isVisible()){
        ((QMenu*)(tray_icon_menu))->actions().at(0)->setDisabled(false);
        ((QMenu*)(tray_icon_menu))->actions().at(1)->setDisabled(true);
    }
    else{
        ((QMenu*)(tray_icon_menu))->actions().at(0)->setDisabled(true);
        ((QMenu*)(tray_icon_menu))->actions().at(1)->setDisabled(false);
    }
    ((QMenu*)(tray_icon_menu))->actions().at(3)->setChecked(ui_menu.quickResultCheckBox->isChecked());
    ((QMenu*)(tray_icon_menu))->actions().at(3)->setText(QString("&Quick Result\n("+ui_menu.keySequenceEdit->keySequence().toString()+")"));
}

void MainWindow::setShortcut(const QKeySequence &sequence){
    this->nativeHotkey->setShortcut(sequence,ui_menu.quickResultCheckBox->isChecked());
    //save quick dict shortcut instanty
    settings.setValue("quickdict_shortcut",sequence);
}

//get supported voice list from pronounce webview
void MainWindow::get_voices(QVariant v){
    ui->voiceList->clear();
  for(int i=0;i<v.value<QVariantList>().count();i++){
        ui->voiceList->addItem(v.value<QVariantList>().at(i).toMap().value("name").toString());
   }
}

void MainWindow::get_selected_word_fromX11(){
    QProcess *xsel = new QProcess(this);
    xsel->setObjectName("xclip");
    xsel->start("xclip",QStringList()<<"-o"<<"-sel");
    connect(xsel,SIGNAL(finished(int)),this,SLOT(set_x11_selection()));
}

void MainWindow::set_x11_selection(){
    QObject *xselection = this->findChild<QObject*>("xclip");
    x11_selected =((QProcess*)(xselection))->readAllStandardOutput();
    if(!x11_selected.trimmed().isEmpty())
      show_requested_word();

    ((QProcess*)(xselection))->deleteLater();
    xselection->deleteLater();
}

void MainWindow::show_requested_word(){
    if(!instant_result_widget->isVisible())
    {
        connect(ui_instant_result.word,SIGNAL(textChanged(QString)),ui->lineEdit,SLOT(setText(QString)));
        ui_instant_result.word->setText(x11_selected.trimmed());

        instant_result_widget->move(QApplication::desktop()->screen()->rect().center()-instant_result_widget->rect().center());

        instant_result_widget->show();
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  if(event->type() == QEvent::MouseButtonRelease)
  {
      if (obj == ui->textBrowser->viewport())textSelectionChanged();

      if(obj == ui->textBrowser_2->viewport())textBrowser_2_selectionChanged();

      if(obj == ui->wikipediaWebview)wikiWebViewSelectionChnaged();

      if(obj == ui->kdictWebview)kdictWebViewSelectionChnaged();

      if(obj == ui->wordnetTextBrowser->viewport())wordnetTextBrowserSelectionChanged();

  }

  return false;
}

void MainWindow::textSelectionChanged()
{
    QString selection = ui->textBrowser->textCursor().selectedText().trimmed();
    if(!selection.isEmpty()){
        ui->lineEdit->setText(selection);
    }
}

void MainWindow::textBrowser_2_selectionChanged()
{
    QString selection = ui->textBrowser_2->textCursor().selectedText().trimmed();
    if(!selection.isEmpty()){
        ui->lineEdit->setText(selection);
    }
}

void MainWindow::wikiWebViewSelectionChnaged(){
    QString selection = ui->wikipediaWebview->selectedText().trimmed(); //textCursor().selectedText().trimmed();
      if(!selection.isEmpty()){
          ui->lineEdit->setText(selection);
      }
}

void MainWindow::kdictWebViewSelectionChnaged(){
    QString selection = ui->kdictWebview->selectedText().trimmed(); //textCursor().selectedText().trimmed();
      if(!selection.isEmpty()){
          ui->lineEdit->setText(selection);
      }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QObject *spliter1 = this->findChild<QObject*>("split1");
    QObject *spliter2 = this->findChild<QObject*>("split2");
    settings.setValue("splitter1State",  ((QSplitter*)(spliter1))->saveState());
    settings.setValue("splitter2State",  ((QSplitter*)(spliter2))->saveState());

    //save live search settings
    settings.setValue("livesearch",ui_menu.liveSearchcheckBox->isChecked());

    //save bottom panel settings
    settings.setValue("bottomPanel",ui_menu.bottomPanelCheckBox->isChecked());

    //save quick dict shortcut
    settings.setValue("quickdict_shortcut",ui_menu.keySequenceEdit->keySequence());

    //save quickdict settings
    settings.setValue("quickdict",ui_menu.quickResultCheckBox->isChecked());

    QMainWindow::closeEvent(event);
}



void MainWindow::init_webviews(){
    QString setting_path =  QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString cookieJarPath ;
    if(setting_path.split("/").last().isEmpty()){
       cookieJarPath  =  setting_path+"/cookiejar_kdict.dat";
    }else{
       cookieJarPath  =  setting_path+"cookiejar_kdict.dat";
    }
//    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
//    QWebSettings::globalSettings()->enablePersistentStorage(setting_path);
//    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    ui->ImageSearchWebview->page()->setNetworkAccessManager(manager);
    ui->wikipediaWebview->page()->setNetworkAccessManager(manager);
    ui->kdictWebview->page()->setNetworkAccessManager(manager);

    ui->ImageSearchWebview->page()->settings()->setMaximumPagesInCache(10);
    ui->wikipediaWebview->page()->settings()->setMaximumPagesInCache(10);
    ui->kdictWebview->page()->settings()->setMaximumPagesInCache(10);


    QNetworkDiskCache* diskCache = new QNetworkDiskCache(this);
    diskCache->setCacheDirectory(setting_path);
    manager->setCache(diskCache);
    manager->setCookieJar(new CookieJar(cookieJarPath, manager));

    ui->kdictWebview->setContextMenuPolicy(Qt::NoContextMenu);
    ui->wikipediaWebview->setContextMenuPolicy(Qt::NoContextMenu);
    ui->ImageSearchWebview->setContextMenuPolicy(Qt::NoContextMenu);
    ui->textBrowser_2->setContextMenuPolicy(Qt::NoContextMenu);
    ui->textBrowser->setContextMenuPolicy(Qt::NoContextMenu);
    ui->wordnetTextBrowser->setContextMenuPolicy(Qt::NoContextMenu);
}

void MainWindow::readSettings()
{
    if(settings.value("geometry").isValid()){
        restoreGeometry(settings.value("geometry").toByteArray());
    }
    if(settings.value("windowState").isValid()){
        restoreState(settings.value("windowState").toByteArray());
    }else{
        this->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());
    }
    QObject *spliter1 = this->findChild<QObject*>("split1");
    QObject *spliter2 = this->findChild<QObject*>("split2");
    ((QSplitter*)(spliter1))->restoreState(settings.value("splitter1State").toByteArray());
    ((QSplitter*)(spliter2))->restoreState(settings.value("splitter2State").toByteArray());


    // live saearch
    if(settings.value("livesearch").isValid()){
        ui_menu.liveSearchcheckBox->setChecked(settings.value("livesearch").toBool());
    }else{
        ui_menu.liveSearchcheckBox->setChecked(true);
    }

    //bottom panel
    if(settings.value("bottomPanel").isValid()){
        ui_menu.bottomPanelCheckBox->setChecked(settings.value("bottomPanel").toBool());
    }else{
        ui_menu.bottomPanelCheckBox->setChecked(true);
    }


     //quick dict settings
     if(settings.value("quickdict").isValid()){
         ui_menu.quickResultCheckBox->setChecked(settings.value("quickdict").toBool());
     }else if(settings.value("quickdict").isValid()){
         ui_menu.quickResultCheckBox->setChecked(true);
     }else{
         ui_menu.quickResultCheckBox->setChecked(false);
     }
    //quick dict key sequence
    if(settings.value("quickdict_shortcut").isValid()){
        QKeySequence k = QKeySequence(settings.value("quickdict_shortcut").toString());
        ui_menu.keySequenceEdit->setKeySequence(k);
        this->nativeHotkey->setShortcut(k.toString(),settings.value("quickdict").toBool());
    }
    else{
        //default value if value not founds
        QKeySequence k = QKeySequence::fromString(tr("Ctrl+Shift+Space"));
        ui_menu.keySequenceEdit->setKeySequence(k);
        this->nativeHotkey->setShortcut(k.toString(),true);
        ui_menu.quickResultCheckBox->setChecked(true);
    }

    //default kdict and save load
    if(settings.value("default_kdict").isValid()){
        ui->dictCombo->setCurrentIndex(settings.value("default_kdict").toInt());
    }else{
        settings.setValue("default_kdict",ui->dictCombo->count()-1);
        ui->dictCombo->setCurrentIndex(settings.value("default_kdict").toInt());
    }

//settings are saved at close event
}



void MainWindow::language_changed(int i){
    QString lang = lang_codes.at(i);
    online_search(ui->wiktionaryLineEdit->text(),lang);
}

void MainWindow::setStyle(QString fname)
{   QFile styleSheet(fname);
    if (!styleSheet.open(QIODevice::ReadOnly)) {
        qWarning("Unable to open file");
    return; }
    qApp->setStyleSheet(styleSheet.readAll());
    styleSheet.close();
}

//mouse event to handle window drag through desktop
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event ->buttons() & Qt::LeftButton) {
        move(event->globalPos() - oldPos);
        event->accept();
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        oldPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}
void MainWindow::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton )
    {
//       qDebug()<<"damn";
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
        ui->listWidget->clear();
        //qDebug() << db.lastError();
        QSqlQuery query;
        query.exec("SELECT word, wordtype FROM main.entries WHERE word LIKE'"+ui->lineEdit->text()+"%' ORDER BY word ASC");
        QStringList found;
        while(query.next()){
           found.append(query.value(0).toString());
        }
        //remove duplicate results coming from database
        for (int i=0; i<found.count(); ++i)
        {
           forever { // remove all occurrences at greater indexes
              int p=found.lastIndexOf(found.at(i));
              if (p==i) break;
              found.removeAt(p);
           }
        }

        ui->listWidget->addItems(found);
        ui->statusBar->showMessage("Showing "+QString::number(found.count())+" results for "+ui->lineEdit->text());
        if(found.count()>0){
            ui->listWidget->setCurrentRow(0); ;
         }


}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    if(currentRow>-1){
        ui->textBrowser->clear();
        QString word = ui->listWidget->item(currentRow)->text().split(" (").first();
        query_word(word,currentRow);
        ui->fakeLineEdit->setText(word);



        ui->readableTextEdit->setText(word);
        ui->Wikipedia_searchLineEdit->setText(word);
        ui->imageSearchLineEdit->setText(word);
        ui->kdictLineEdit->setText(word);
        ui->wiktionaryLineEdit->setText(word);
        ui->wordnetsearchLineEdit->setText(word);

        ui_instant_result.meaning->setText(ui->textBrowser->toHtml());
    }else{
            ui->textBrowser->setText("<i style='color:red'>No definition found for <b>"+ui->lineEdit->text()+"</b></i>");
            ui_instant_result.meaning->clear();
    }


}

void MainWindow::query_word(QString word, int i)
{
    word = word.trimmed();
    Q_UNUSED(i);
       // qDebug() << db.lastError();
        QSqlQuery query;
        query.exec("SELECT definition,wordtype FROM main.entries WHERE word ='"+word+"'");
        if(query.record().count()>0){
            while(query.next()){
                //    qDebug()<<i<<word<<query.value(0).toString();
                    show_meaning(word,query,1);
            }
        }else{
            show_meaning(word,query,0);
        }

}

void MainWindow::show_meaning(QString word, QSqlQuery query, bool isArray){
    if(isArray){
        ui->textBrowser->append("<br><b>"+word.toUpper()+"</b> ("+query.value(1).toString()+") <br><br>"+query.value(0).toString());
    }else ui->textBrowser->setText("<b>"+word.toUpper()+"</b><br><br>"+query.value(0).toString());
    QTextCursor cursor = ui->textBrowser->textCursor();
    cursor.setPosition(0);
    ui->textBrowser->setTextCursor(cursor);

}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    //start search if search term length counts more then 1 chars
    if(arg1.length()>=1){
        if(!ui->pushButton->isVisible()){
            on_pushButton_clicked();
        }else{
            if(this->windowState()==Qt::WindowMinimized||!this->isVisible()){
               on_pushButton_clicked();
            }
        }
        ui->pushButton->setEnabled(true);
        ui->favurite_btn->setEnabled(true);
        favLoaded = false;

    }else{
        ui->favurite_btn->setEnabled(false);
        ui->pushButton->setEnabled(false);
    }
    //get first char of text
    QString s = arg1.at(0).toUpper();
    QString alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int pos_in_list = alpha.indexOf(s);
   // qDebug()<<s<<pos_in_list;
    ui->listWidget_2->setCurrentRow(pos_in_list);
    //QCharRef lastchar = s[s.length()+s.length()];

    //clears list when search is empty
    if(arg1.length()==0){
        ui->listWidget->clear();
        ui->textBrowser->clear();
    }else{
        QString word = ui->lineEdit->text();
        ui->readableTextEdit->setText(word);
        ui->Wikipedia_searchLineEdit->setText(word);
        ui->imageSearchLineEdit->setText(word);
        ui->kdictLineEdit->setText(word);
        ui->wiktionaryLineEdit->setText(word);
        ui->wordnetsearchLineEdit->setText(word);
    }
    ui->pushButton->setEnabled(!arg1.trimmed().isEmpty());

    hisLoaded = false;
//ui->clear_his->hide();
}

void MainWindow::online_search(QString word,QString lang){
    QString loadText = "<h4>Loading result for - "+word+" ...</h4>";
    if(lang=="null"){
        QNetworkRequest request(QUrl("http://ktechpit.com/wiktionary/?q="+word+"&lang="+lang_codes.at(ui->language->currentIndex())));
        reply =m_network_manager.get(request);
        ui->textBrowser_2->setHtml(loadText);
    }else{
        QNetworkRequest request(QUrl("http://ktechpit.com/wiktionary/?q="+word+"&lang="+lang));
        reply =m_network_manager.get(request);
        ui->textBrowser_2->setHtml(loadText);
    }
    connect(this->reply,SIGNAL(finished()),this,SLOT(request_done()));
}

void MainWindow::request_done(){

  if(reply->error()== QNetworkReply::NoError){
   QByteArray ans= reply->readAll();
   QString s_data = QTextCodec::codecForMib(106)->toUnicode(ans);  //106 is textcode for UTF-8 here --- http://www.iana.org/assignments/character-sets/character-sets.xml
   ui->textBrowser_2->setHtml(s_data);
  }else{
//      QString eror =reply->errorString();
      show_net_error_message(false);
  }
}

void MainWindow::on_lineEdit_returnPressed()
{
    //search btn substitute
    ui->listWidget->clear();
    on_pushButton_clicked();
    ui->wordnetsearchLineEdit->setText(ui->lineEdit->text());
    on_wordnetSearchBtn_clicked();
}

void MainWindow::on_close_btn_clicked()
{
    if(showMsgBox){
        if(settings.value("minimize_on_close").toBool()){
            QMessageBox msgBox;
            msgBox.setText("<b>Window Manager:</b>");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setInformativeText("Minimize Application in system tray ?\n[Tip]:Click Restore option in system tray icon to Open Application.\n\n"+shortCut_set_check_return());

            QAbstractButton *quit =
                    msgBox.addButton(tr("Quit"), QMessageBox::ActionRole);

            msgBox.addButton(QMessageBox::Cancel);
            msgBox.addButton(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.button(QMessageBox::Cancel)->hide();

            QCheckBox *cb = new QCheckBox("Okay I understand");
            cb->setChecked(false);
            msgBox.setCheckBox(cb);

            QObject::connect(cb, &QCheckBox::stateChanged, [this](int state){
                    if (static_cast<Qt::CheckState>(state) == Qt::CheckState::Checked) {
                        this->showMsgBox = false;
                    }
             });

            int ret = msgBox.exec();

            if(ret==QMessageBox::Ok)this->hide();
            else if(ret==QMessageBox::Cancel)msgBox.close();
            else if(msgBox.clickedButton()==quit)this->close();
            else msgBox.hide();

        }else{
            this->close();
        }
    }else{
        this->hide();
    }
}

QString MainWindow::shortCut_set_check_return(){
    if(ui_menu.minimize_to_tray->isChecked()){
        return QString("Quick result is enabled and can be evoked anytime with \""+ui_menu.keySequenceEdit->keySequence().toString()+"\" shortcut combination.\nSelect a word and press shortcut combination to get instant meaning.");
    }else return QString("Fuck");
}


void MainWindow::on_max_btn_clicked()
{
    if(this->windowState()==Qt::WindowMaximized){
        this->setWindowState(Qt::WindowNoState );
    }else{
        this->setWindowState((Qt::WindowMaximized));
    }
}

void MainWindow::on_min_btn_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}


void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    if(!item->text().isEmpty()){
        ui->lineEdit->setText(item->text());
    }
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch (index){
    case 1:
        if(!ui->kdictWebview->url().toString().contains(ui->kdictLineEdit->text()))
        if(ui->kdictSearchBtn->isEnabled())on_kdictSearchBtn_clicked();
        break;
    case 3:
        if(!ui->wikipediaWebview->url().toString().contains(ui->Wikipedia_searchLineEdit->text()))
        if(ui->wikipedia_searchBtn->isEnabled())on_wikipedia_searchBtn_clicked();
        break;
    case 4:
        if(!ui->textBrowser_2->toPlainText().contains(ui->wiktionaryLineEdit->text()))
        if(ui->wiktionaryPushButton->isEnabled())on_wiktionaryPushButton_clicked();
        break;
    case 5:
        if(!word_for_image_search.contains(ui->imageSearchLineEdit->text()))
        if(ui->imageSearchBtn->isEnabled())on_imageSearchBtn_clicked();
        break;
    default:
        break;
    }
}

void MainWindow::on_wiktionaryPushButton_clicked()
{
    online_search(ui->wiktionaryLineEdit->text(),lang_codes.at(ui->language->currentIndex()));
}

void MainWindow::on_read_textPushBtn_clicked()
{
    QString text = ui->readableTextEdit->toPlainText().replace("(n.)","-").replace("(v.)","-");
    ui->pronounceWebview->page()->mainFrame()->evaluateJavaScript("responsiveVoice.speak('"+text.remove(QRegExp("[\\n\\t\\r])"))+"', '"+ui->voiceList->currentText()+"',{volume: 1});");

}

void MainWindow::on_read_DefinitionPushBtn_clicked()
{
    ui->readableTextEdit->setText(ui->textBrowser->toPlainText().remove(QRegExp("[\\n\\t\\r]")));
    QString text = ui->readableTextEdit->toPlainText().replace("(n.)","-").replace("(v.)","-");
    ui->pronounceWebview->page()->mainFrame()->evaluateJavaScript("responsiveVoice.speak('"+text.remove(QRegExp("[\\n\\t\\r])"))+"', '"+ui->voiceList->currentText()+"',{volume: 1});");

}

void MainWindow::on_read_abovePushBtn_clicked()
{
    QString text = ui->readableTextEdit->toPlainText().replace("(n.)","-").replace("(v.)","-");
    ui->pronounceWebview->page()->mainFrame()->evaluateJavaScript("responsiveVoice.speak('"+text.remove(QRegExp("[\\n\\t\\r])"))+"', '"+ui->voiceList->currentText()+"',{volume: 1});");
}

void MainWindow::on_stop_reading_PushBtn_clicked()
{
    ui->pronounceWebview->page()->mainFrame()->evaluateJavaScript("responsiveVoice.cancel();");
}

void MainWindow::on_pausePushBtn_clicked()
{
    ui->pronounceWebview->page()->mainFrame()->evaluateJavaScript("if(responsiveVoice.isPlaying()){responsiveVoice.pause()}");
}

void MainWindow::on_resumePushBtn_2_clicked()
{
    ui->pronounceWebview->page()->mainFrame()->evaluateJavaScript("if(!responsiveVoice.isPlaying()){responsiveVoice.resume()}");
}

//send the current voice type to webview
QString MainWindow::get_selectedVoice(){
    return voiceType;
}

void MainWindow::on_voiceList_currentIndexChanged(const QString &arg1)
{
  voiceType=arg1;
}

void MainWindow::on_kdictSearchBtn_clicked()
{

    asked_by_instant_result = false;
    QUrl url = "http://services.aonaware.com/DictService/Default.aspx?action=define&dict="+dicts.at(ui->dictCombo->currentIndex())+"&query="+ui->kdictLineEdit->text();

    ui->kdictWebview->settings()->setUserStyleSheetUrl(QUrl("qrc:/kdict/kdict/dict.css"));
    ui->kdictWebview->load(url);
    ui->kdictWebview->hide();
//    ui->kdictWebview->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
//    ui->kdictWebview->page()->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);

}

void MainWindow::kdictView_progress(int value){
    ui->kdictProgressBar->setValue(value);

    if(value<100&&value>1){
         ui->kdictProgressBar->show();
      }
    else{
         ui->kdictProgressBar->hide();
    }
}

void MainWindow::kdictView_loaded(bool loaded){

    QString js ="document.querySelector('#pnlQuery').innerHTML='';"
    "var paras = document.querySelectorAll('p');"
    "paras[paras.length-1].innerHTML='';"
    "document.querySelectorAll('hr')[0].outerHTML='';";

    if(loaded){
        ui->kdictWebview->page()->mainFrame()->evaluateJavaScript(js);
        ui->kdictWebview->show();
        if(asked_by_instant_result)ui_instant_result.meaning->setPlainText(ui->kdictWebview->page()->mainFrame()->toPlainText().remove("From WordNet (r) 2.0:"));
     }else{
        ui->kdictWebview->hide();
        show_net_error_message(loaded);
    }
    QString url_string=ui->kdictWebview->url().toString() ;
    QString dict;
    for(int i=0;i<dicts.count();i++){
      dict = "&dict="+dicts.at(i);
      if(url_string.contains(dict)){
          ui->dictCombo->setCurrentIndex(i);
      }
     }
    ui->kdictLineEdit->setText(url_string.split("&query=").last().replace("+"," "));
}

void MainWindow::show_net_error_message(bool b){
    if(!b)
    {
        QMessageBox msgBox;
        msgBox.setText("Unable to load data or connect to internet !");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Close);
        msgBox.setDefaultButton(QMessageBox::Close);
        msgBox.exec();
    }

}

void MainWindow::evaluateClickedLink_in_kdictWebPage(QUrl url)
{
    if(!url.toString().contains("dictinfo")){ //to not load dictinfo

    if(!ui->kdictWebview->page()->mainFrame()->toHtml().contains("No definitions found")){

        QString url_string = url.toString();
        QString selected_dict = dicts.at(ui->dictCombo->currentIndex());
        QString dict,newUrl;
        for(int i=0;i<dicts.count();i++){
          dict = "&dict="+dicts.at(i);
          if(url_string.contains(dict)){
              ui->dictCombo->setCurrentIndex(i);
              newUrl = url_string.replace(dicts.at(i),selected_dict);
           }
         }
        ui->kdictWebview->load(QUrl(newUrl));
    }else{
         ui->kdictWebview->load(url);
    }
  }
}

void MainWindow::on_wikipedia_searchBtn_clicked()
{
    QUrl url = "http://ktechpit.com/wiktionary/wikipedia_api/search.php?q="+ui->Wikipedia_searchLineEdit->text();
       ui->wikipediaWebview->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    ui->wikipediaWebview->settings()->setUserStyleSheetUrl(QUrl("qrc:/wikipedia/wikipedia/dict.css"));
    ui->wikipediaWebview->load(url);
    ui->wikipediaWebview->hide();

}

void MainWindow::wikiWebView_progress(int value){
    ui->wikiProgressBar->setValue(value);

    if(value<100&&value>1){
         ui->wikiProgressBar->show();
      }
    else{
         ui->wikiProgressBar->hide();
    }
}

void MainWindow::wikiWebView_loaded(bool loaded){

    if(loaded){
         ui->wikipediaWebview->show();
     }else{
        ui->wikipediaWebview->hide();
        show_net_error_message(loaded);
    }
}



void MainWindow::on_imageSearchBtn_clicked()
{
    word_for_image_search = ui->imageSearchLineEdit->text();
//  QNetworkRequest request(QUrl("http://images.google.com/search?q="+word+"&tbm=isch&sout=1")); //basic
    QUrl url = "https://www.google.co.in/search?q="+word_for_image_search+"&source=lnms&tbm=isch";
    QNetworkRequest request(url);

    request.setRawHeader("User-Agent","'User-Agent':\"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/43.0.2357.134 Safari/537.36\"");
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    images_reply = manager->get(request);

    ui->imageSearchProgressBar->show();
    ui->imageSearchProgressBar->setMaximum(0);
    ui->imageSearchProgressBar->setMinimum(0);
    ui->imageSearchProgressBar->setValue(0);

    QString setting_path =  QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString cookieJarPath ;
    if(setting_path.split("/").last().isEmpty()){
       cookieJarPath  =  setting_path+"/cookiejar_kdict.dat";
    }else{
       cookieJarPath  =  setting_path+"cookiejar_kdict.dat";
    }
    QNetworkDiskCache* diskCache = new QNetworkDiskCache(this);
    diskCache->setCacheDirectory(setting_path);
    manager->setCache(diskCache);
    manager->setCookieJar(new CookieJar(cookieJarPath, manager));

    connect(this->images_reply,SIGNAL(finished()),this,SLOT(images_request_done()));
}

void MainWindow::images_request_done(){

    if(images_reply->error()== QNetworkReply::NoError){
        QByteArray ans= images_reply->readAll();
        QString s_data1,s_data2;
        QString s_data = QTextCodec::codecForMib(106)->toUnicode(ans);  //106 is textcode for UTF-8 here --- http://www.iana.org/assignments/character-sets/character-sets.xml
        s_data1 = s_data.split("<table class=").last();
        s_data2 = s_data1.split("</table>").first();


        QRegExp imgTagRegex("<img.*src=\"(.*)\".*>", Qt::CaseInsensitive);
        imgTagRegex.setMinimal(true);
        QStringList urlMatches;
        QStringList imgMatches;
        int offset = 0;
        while(offset >= 0)
        {
            offset = imgTagRegex.indexIn(s_data2, offset);
            offset += imgTagRegex.matchedLength();

            QString imgTag = imgTagRegex.cap(0);
            if (!imgTag.isEmpty())
                imgMatches.append(imgTag);

            QString url = imgTagRegex.cap(1);
            if (!url.isEmpty())
            {
                url = url.split("\"").first();
                if (!urlMatches.contains(url))
                    urlMatches.append(url);
            }
        }

        QString html,css;
        css = "<html lang='en'><head><style type='text/css'>::-webkit-scrollbar{width:8px;height:8px}::-webkit-scrollbar-button{width:0;height:0}::-webkit-scrollbar-thumb{background:#B7B7B7;border:0 none #fff;border-radius:0}::-webkit-scrollbar-thumb:hover{background:#B7B7B7}::-webkit-scrollbar-thumb:active{background:#B7B7B7}::-webkit-scrollbar-track{background:#323232;border:0 none #fff;border-radius:0}::-webkit-scrollbar-track:hover{background:#323232}::-webkit-scrollbar-track:active{background:#323232}::-webkit-scrollbar-corner{background:transparent}img{height:auto;max-width:100%}"
              ".image-table{border:0 solid rgba(0,0,0,0);border-collapse:separate;border-spacing:6px;table-layout:fixed;text-align:center;width:100%}.image-table img{border:0px solid #3DAEE9;box-sizing:border-box;-webkit-box-shadow:0 0 10px #3DAEE9;box-shadow:0 0 10px #3DAEE9}body{height:inherit!important;color:#fff!important;background:url(http://ktechpit.com/wiktionary/wikipedia_api/mainfeatures.png);background-size:cover;background-color:transparent!important;background-repeat:no-repeat;background-attachment:fixed}</style></head>";

//        qDebug()<<urlMatches.count()<<"returened imgs";

        if(urlMatches.count()>1){

           urlMatches.removeAt(0);

                html.append("<tr>");
                for(int i=0;i<4;i++){
                        html.append("<td><img width='220px' height='220px' src='"+urlMatches.at(i)+"'></img></td>");
                    }
                html.append("</tr>");
                html.append("<tr>");
                for(int i=4;i<8;i++){
                        html.append("<td><img width='220px' height='220px' src='"+urlMatches.at(i)+"'></img></td>");
                    }
                html.append("</tr>");
                html.append("<tr>");
                for(int i=8;i<12;i++){
                        html.append("<td><img width='220px' height='220px' src='"+urlMatches.at(i)+"'></img></td>");
                    }
                html.append("</tr>");
                html.append("<tr>");
                for(int i=12;i<16;i++){
                        html.append("<td><img width='220px' height='220px' src='"+urlMatches.at(i)+"'></img></td>");
                    }
                html.append("</tr>");
                html.append("<tr>");
                for(int i=16;i<20;i++){
                        html.append("<td><img width='220px' height='220px' src='"+urlMatches.at(i)+"'></img></td>");
                    }
                html.append("</tr>");
                html.append("<tr>");
                for(int i=20;i<24;i++){
                        html.append("<td><img width='220px' height='220px' src='"+urlMatches.at(i)+"'></img></td>");
                    }
                html.append("</tr>");
                html.append("<tr>");
                for(int i=24;i<28;i++){
                        html.append("<td><img width='220px' height='220px' src='"+urlMatches.at(i)+"'></img></td>");
                    }
                html.append("</tr>");
                html.append("<tr>");
                for(int i=28;i<32;i++){
                        html.append("<td><img width='220px' height='220px' src='"+urlMatches.at(i)+"'></img></td>");
                    }
                html.append("</tr>");
//      ui->ImageSearchWebview->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
        ui->ImageSearchWebview->setHtml(css+"<table class='image-table'><tbody>"+html+"</tbody></table>");

        }
    }else{
        QString eror =images_reply->errorString();
        show_net_error_message(false);

        ui->imageSearchProgressBar->hide();
    }
}

void MainWindow::imageView_progress(int value){
    ui->imageSearchProgressBar->setMaximum(100);
    ui->imageSearchProgressBar->setMinimum(0);
    ui->imageSearchProgressBar->setValue(value);

    if(value<100&&value>1){
         ui->imageSearchProgressBar->show();
      }
    else{
         ui->imageSearchProgressBar->hide();
    }
}


void MainWindow::on_imageSearchLineEdit_returnPressed()
{
    ui->imageSearchBtn->click();
}

void MainWindow::on_wiktionaryLineEdit_returnPressed()
{
    ui->wiktionaryPushButton->click();
}

void MainWindow::on_Wikipedia_searchLineEdit_returnPressed()
{
    ui->wikipedia_searchBtn->click();
}

void MainWindow::on_kdictLineEdit_returnPressed()
{
    ui->kdictSearchBtn->click();
}

void MainWindow::on_dictCombo_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    ui->kdictSearchBtn->click();
    settings.setValue("default_kdict",index);
}

void MainWindow::on_kdictLineEdit_textChanged(const QString &arg1)
{
        ui->kdictSearchBtn->setEnabled(!arg1.trimmed().isEmpty());
}

void MainWindow::on_Wikipedia_searchLineEdit_textChanged(const QString &arg1)
{
    ui->wikipedia_searchBtn->setEnabled(!arg1.trimmed().isEmpty());
}

void MainWindow::on_wiktionaryLineEdit_textChanged(const QString &arg1)
{
    ui->wiktionaryPushButton->setEnabled(!arg1.trimmed().isEmpty());
}

void MainWindow::on_imageSearchLineEdit_textChanged(const QString &arg1)
{
    ui->imageSearchBtn->setEnabled(!arg1.trimmed().isEmpty());
}


void MainWindow::init_main_menu(){
    ui_menu_widget = new QWidget();
    ui_menu.setupUi(ui_menu_widget);
    connect(ui_menu.exit,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui_menu.liveSearchcheckBox,SIGNAL(toggled(bool)),this,SLOT(liveSearchcheckBoxToggled(bool)));
    connect(ui_menu.bottomPanelCheckBox,SIGNAL(toggled(bool)),this,SLOT(bottomPanelCheckBoxToggled(bool)));
    connect(ui_menu.showFavBtn,SIGNAL(clicked(bool)),this,SLOT(showFav()));
    connect(ui_menu.hisBtn,SIGNAL(clicked(bool)),this,SLOT(showHis()));

    connect(ui_menu.minimize_to_tray,SIGNAL(toggled(bool)),this,SLOT(minimizeApp_in_tray(bool)));
    connect(ui_menu.clearHistory,SIGNAL(clicked(bool)),this,SLOT(clear_his_clicked()));


    connect(ui_menu.website,SIGNAL(clicked(bool)),this,SLOT(open_website()));
    connect(ui_menu.paypal,SIGNAL(clicked(bool)),this,SLOT(open_website()));
    connect(ui_menu.contact,SIGNAL(clicked(bool)),this,SLOT(open_website()));

    QList<QPushButton*> button_list = ui_menu_widget->findChildren<QPushButton *>();
   for(int i =0; i <button_list.size(); i++)
   {
          button_list.at(i)->setStyleSheet(btn_style);
   }
   ui_menu.paypal->setStyleSheet("border:none;background-color: transparent;");
   ui_menu.paypal->resize(QSize(ui_menu.exit->size()));
   ui_menu.exit->setStyleSheet("border:none;background-color: transparent;");

    ui_menu_widget->setWindowFlags(Qt::Popup);
    ui_menu_widget->resize(ui_menu_widget->minimumSizeHint());

    //load minimize_on_close setting
    if(settings.value("minimize_on_close").isValid()){
        ui_menu.minimize_to_tray->setChecked(settings.value("minimize_on_close").toBool());
    }else{
        ui_menu.minimize_to_tray->setChecked(true);
    }
}


void MainWindow::open_website()
{

    QStringList options;
    options<< "website" << "paypal" << "contact";

    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    QString title =  senderButton->objectName();

    switch (options.indexOf(title)) {
    case 0:{
        QDesktopServices::openUrl(QUrl("http://ktechpit.com"));
    }
    break;
    case 1:{
        QDesktopServices::openUrl(QUrl("https://paypal.me/keshavnrj/4"));
    }
    break;
    case 2:{
        QDesktopServices::openUrl(QUrl("mailto:keshavnrj@gmail.com"));
    }
    break;
    default:
        QDesktopServices::openUrl(QUrl("http://ktechpit.com"));
        break;
    }
}


void MainWindow::minimizeApp_in_tray(bool b){
    settings.setValue("minimize_on_close",b);
}



void MainWindow::liveSearchcheckBoxToggled(bool b){

        ui->pushButton->setVisible(!b);
}

void MainWindow::bottomPanelCheckBoxToggled(bool b){

    ui->verticalWidgetOnline->setVisible(b);
}

void MainWindow::init_instant_result(){
    asked_by_instant_result =false;

    instant_result_widget = new QWidget();
    ui_instant_result.setupUi(instant_result_widget);

    QList<QPushButton*> button_list = instant_result_widget->findChildren<QPushButton *> ();
    for(int i =0; i <button_list.size(); i++)
    {
           button_list.at(i)->setStyleSheet(btn_style);
    }
    instant_result_widget->setWindowFlags(Qt::Popup);
    instant_result_widget->resize(instant_result_widget->minimumSizeHint());
    connect(ui_instant_result.pronounce,SIGNAL(clicked(bool)),this,SLOT(on_read_textPushBtn_clicked()));
    connect(ui_instant_result.readDef,SIGNAL(clicked(bool)),this,SLOT(on_read_DefinitionPushBtn_clicked()));
    connect(ui_instant_result.close,SIGNAL(clicked(bool)),instant_result_widget,SLOT(close()));
    connect(ui_instant_result.maximize,SIGNAL(clicked(bool)),this,SLOT(show_MainWindow()));
    connect(ui_instant_result.ask_word_netBtn,SIGNAL(clicked(bool)),this,SLOT(ask_word_net(bool)));

}

void MainWindow::show_MainWindow(){
        instant_result_widget->close();
        this->activateWindow();
        this->show();
}

void MainWindow::ask_word_net(bool b)
{
    Q_UNUSED(b);
    asked_by_instant_result = true;
    QUrl url = "http://services.aonaware.com/DictService/Default.aspx?action=define&dict=wn&query="+ui->kdictLineEdit->text();
    ui->kdictWebview->settings()->setUserStyleSheetUrl(QUrl("qrc:/kdict/kdict/dict.css"));
    ui->kdictWebview->load(url);
    ui->kdictWebview->hide();
}

void MainWindow::on_menu_clicked()
{
    if(!ui_menu_widget->isVisible())
    {
        ui_menu_widget->move(ui->menu->mapToGlobal(QPoint(((-ui_menu_widget->width())-(-ui_menu_widget->width()/8)),ui->menu->height()+8)));
        ui_menu_widget->resize(ui_menu_widget->minimumSizeHint());
        ui_menu_widget->adjustSize();
        ui_menu_widget->show();
    }
    ui_menu.version->setText("Version : "+QApplication::applicationVersion());
}


//wordnet 3.0 from system
void MainWindow::on_wordnetSearchBtn_clicked()
{
    QProcess *wn = new QProcess(ui->close_btn);
    wn->setObjectName("wn");

//#!/bin/sh
//export PATH=$SNAP/usr/bin
//export WNHOME=$SNAP/usr/share/wordnet
//export WNSEARCHDIR=$SNAP/usr/share/wordnet
//Mwn $1 $2


//COMMENTED BECAUSE NOW USING ABOVE WRAPPER SCRIPT INSIDE SNAP FOR "wn" command

//    for snap use only------------------------------------------------------------
//    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
//    env.insert("PATH","$SNAP/usr/bin");
//    env.insert("WNHOME", "$SNAP/usr/share/wordnet");
//    env.insert("WNSEARCHDIR","$SNAP/usr/share/wordnet");
//    wn->setProcessEnvironment(env);
//    for snap use only------------------------------------------------------------

//COMMENTED BECAUSE NOW USING WRAPPER SCRIPT INSIDE SNAP FOR "wn" command

    wn->start("wn",QStringList()<<ui->wordnetsearchLineEdit->text()<<"-over");
    connect(wn,SIGNAL(finished(int)),this,SLOT(show_wn_result(int)));

//    connect(wn, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
//         [=](int exitCode, QProcess::ExitStatus exitStatus){
//        qDebug()<<exitCode<<exitStatus;
//       Q_UNUSED(exitCode);
//    });

}

void MainWindow::show_wn_result(int exitCode){
    Q_UNUSED(exitCode);
    QObject *wn_ = this->findChild<QObject*>("wn");
    wn_result =((QProcess*)(wn_))->readAllStandardOutput();
    if(!wn_result.trimmed().isEmpty())
       process_wn_output(wn_result);
     else ui->wordnetTextBrowser->setText("<i style='color:red'>No definition found for <b>"+ui->wordnetsearchLineEdit->text()+"</b></i>");
    ((QProcess*)(wn_))->terminate();
     wn_->deleteLater();
     delete wn_;
}

void MainWindow::on_wordnetsearchLineEdit_textChanged(const QString &arg1)
{
    ui->wordnetSearchBtn->setEnabled(!arg1.trimmed().isEmpty());
}

void MainWindow::process_wn_output(QString result){

    QStringList lines;
    lines.append(result.split("\n"));

    QString word= ui->wordnetsearchLineEdit->text().trimmed();
    QString o_t;//overview_type
    QString n_o_s;//number_of_senses
    QString data; //final
    for(int i=0;i<lines.count();i++){
        //remove overview of and get overview type
        if(lines.at(i).contains("Overview of")){
            o_t=lines.at(i).split("Overview of").last().trimmed().split(" ").first();
            lines.removeAt(i);
        }

        //remove [overview_type] has [x] senses
        if(lines.at(i).contains("The "+o_t.trimmed())){
             n_o_s = lines.at(i).split(" has ").last();
             n_o_s= n_o_s.split(" ").first();
             lines.replace(i,QString("<b style='color:#A9E550;'>("+o_t+")</b> <i style='color:#A9E550;'>"+n_o_s+" definition found for "+word+"</i>"));
        }

        //clear brackted numbers
        if (lines.at(i).contains(QRegularExpression("\\(([1-9][0-9]{0,2}|1000)\\)"))){
            lines.replace(i,QString(lines.at(i)).replace(QRegularExpression("\\(([1-9][0-9]{0,2}|1000)\\)")," "));
           }

        //clear definition and get synonyms :D
        QString synonyms,definitions;
        if (lines.at(i).contains(QRegularExpression("[[:space:]].+?( --)"))){
            synonyms = QString(lines.at(i)).split(QRegularExpression("(-- ).+")).first();
            synonyms = synonyms.split(QRegularExpression("[\\d]. ")).last();
            definitions = QString(lines.at(i)).split(QRegularExpression("[[:space:]].+?( --)")).last();
            lines.replace(i,QString("<i style='color:#3DAEE9'><i style='color:#DA2121' >synonym</i>["+synonyms+"]</i>"+definitions));
          }       
        data.append(lines.at(i)+"<br>");
    }

    ui->wordnetTextBrowser->setHtml(data.replace("<br><br>","<br>"));
   // qDebug()<<data;
    wn_result.clear();
}


void MainWindow::on_grepCombo_currentIndexChanged(const QString &arg1)
{
    QProcess *wn_grep = new QProcess(this);
    wn_grep->setObjectName("wn_grep");
    if(arg1.contains(QString("[word-type]"))){
         ui->wordnetSearchBtn->click();
    }

    else{
        wn_grep->closeReadChannel(QProcess::StandardOutput);
        wn_grep->closeReadChannel(QProcess::StandardError);
        wn_grep->closeWriteChannel();
        wn_grep->start("wn",QStringList()<<ui->wordnetsearchLineEdit->text()<<arg1.split(" ").last());

        if(!wn_grep->waitForFinished()){
//          qDebug() << "process failed: " << wn_grep->errorString();
        }
        else{
        QString data;
        wn_result.clear();
        wn_result =wn_grep->readAllStandardOutput();
        if(!wn_result.trimmed().isEmpty()){

       QStringList outputList;
       outputList.append(wn_result.split("\n"));
           outputList.replace(1,QString("<i style='color:#3DAEE9'>"+QString(outputList.at(1)).replace("Grep","Similar word(s) ")+"</i><br>"));
           for(int i=0;i<outputList.count();i++){
               data.append(QString(outputList.at(i))+"<br>");
           }
           ui->wordnetTextBrowser->setText(data);
           data.clear();
       }else{
           ui->wordnetTextBrowser->setText("<i style='color:red'>Nothing Found</i>");
       }
       wn_grep->deleteLater();
       data.clear();
        }
    }
}

void MainWindow::on_wordnetTextBrowser_cursorPositionChanged()
{
//      QList<QTextBrowser::ExtraSelection> extraSelections;

//      QTextBrowser::ExtraSelection selection ;
//      QColor lineColor(61, 174, 233, 42);
      
//      selection.format.setBackground(lineColor);
//      selection.format.setProperty(QTextFormat::FullWidthSelection, true);
//      selection.cursor = ui->wordnetTextBrowser->textCursor();
//      selection.cursor.clearSelection();
//      extraSelections.append(selection);
//      ui->wordnetTextBrowser->setExtraSelections(extraSelections);

}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    Q_UNUSED(item)
    if(ui->wordnetSearchBtn->isEnabled())
    on_wordnetSearchBtn_clicked();
}

void MainWindow::on_wordnetsearchLineEdit_returnPressed()
{
    ui->wordnetSearchBtn->click();
}


void MainWindow::wordnetTextBrowserSelectionChanged()
{
//    qDebug()<<"damn";
    QString selection = ui->wordnetTextBrowser->textCursor().selectedText().trimmed();
    if(!selection.isEmpty()){
        ui->lineEdit->setText(selection);
    }
}

void MainWindow::on_favurite_btn_clicked()
{
    if(isFav){
        rem_fav();
    }else{
        add_fav();
    }
    check_fav();
//    qDebug()<<words_fav<<"at end";
}

void MainWindow::add_fav(){
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) ;
    QFile file(path+"/fav.txt");
     if(!file.open(QIODevice::Append | QIODevice::ReadWrite| QIODevice::Text))
              return;
    QTextStream out(&file);
    if(words_fav.count()>0){
        esp ="\n";
    }else{
        esp.clear();
    }
    out <<esp<<ui->fakeLineEdit->text().trimmed()+"#";
    file.close();
//    qDebug()<<words_fav<<"after write add";
    readed_fav = false;
}

void MainWindow::rem_fav(){
//    qDebug()<<"remove";
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) ;
    QFile file(path+"/fav.txt");
     if(!file.open(QIODevice::Truncate | QIODevice::ReadWrite | QIODevice::Text))
              return;
    QTextStream out(&file);
//qDebug()<<words_fav<<"words in fav before rem";

    for(int i=0;i<words_fav.count();i++){
        QString s = words_fav.at(i);
//        qDebug()<<"called";
        if(s==ui->fakeLineEdit->text().trimmed()+"#"){
//            qDebug()<<ui->lineEdit->text().trimmed() +"#"<<"true";
             words_fav.removeAt(i);
        }
    }

//qDebug()<<words_fav<<"before write remove";


    for(int i=0;i<words_fav.count();i++){
        if(!words_fav.at(i).isEmpty())
             out<<words_fav.at(i)+"\n";
    }
    file.close();
    readed_fav = false;
    //for instant update of list after item removal
    if(favLoaded){
        showFav();
    }
}

void MainWindow::read_favFile(){

    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) ;
    QFile file(path+"/fav.txt");
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
              return;
    //QTextStream out(&file);

    QTextStream in(&file);
    words_fav.clear();
    while(!in.atEnd()){
        words_fav.append(file.readLine().trimmed());
    }
//    qDebug()<<words_fav<<"after file read";
    readed_fav = true;
}

void MainWindow::check_fav(){
    if(!favLoaded){
        ui->listTypeLable->hide();
    }

    if(!readed_fav){
        read_favFile();
    }
//    qDebug()<<words_fav;
    isFav=false;
    for(int i=0;i<words_fav.count();i++){

             if(words_fav.contains(ui->fakeLineEdit->text().trimmed()+"#",Qt::CaseInsensitive)){
                ui->favurite_btn->setIcon(QIcon(":/bs/bs/fav.png"));
                ui->favurite_btn->setToolTip("Remove "+ui->fakeLineEdit->text().trimmed()+" from favourite");
                isFav=true;
            }else{
                ui->favurite_btn->setIcon(QIcon(":/bs/bs/fav2.png"));
                ui->favurite_btn->setToolTip("Add "+ui->fakeLineEdit->text().trimmed()+" favourite");
                isFav=false;
            }
            if(words_fav.count()>0){
                esp ="\n";
            }else{
                esp.clear();
            }
    }
}

void MainWindow::showFav(){
    if(!readed_fav){
         read_favFile();
    }
    ui->listWidget->clear();
    for(int i= 0;i<words_fav.count();i++) {
        if(!words_fav.at(i).isEmpty())
        ui->listWidget->addItem(QString(words_fav.at(i)).remove("#"));
    }
    ui->listTypeLable->setText("Favourite Words");
    ui->listTypeLable->show();
    if(ui->listWidget->count()>0){
        favLoaded =true;
        ui->listWidget->setCurrentRow(0);
    }else{
        ui->favurite_btn->setIcon(QIcon(":/bs/bs/fav2.png"));
        ui->favurite_btn->setToolTip("Add "+ui->fakeLineEdit->text().trimmed()+" to favourite");
        isFav=false;
        favLoaded =false;
        ui->lineEdit->clear();
    }
    ui->statusBar->showMessage("Showing your "+QString::number(words_fav.count())+" favourite words.");
    ui_menu_widget->close();

}

void MainWindow::on_fakeLineEdit_textChanged(const QString &arg1)
{
    ui->favurite_btn->setEnabled(!arg1.isEmpty());
    check_fav();

    if(hisLoaded){
             ui->listTypeLable->setVisible(true);
    }

    if(favLoaded){
             ui->listTypeLable->setVisible(true);
    }

}

//save and load history
void MainWindow::showHis(){
    if(!readed_his){
         readHis();
    }
    ui->listWidget->clear();
    for(int i= 0;i<words_his.count();i++) {
        if(!words_his.at(i).isEmpty())
        ui->listWidget->addItem(QString(words_his.at(i)).remove("#"));
    }
    if(ui->listWidget->count()>0){
        ui->listWidget->setCurrentRow(0);
    }
    ui->statusBar->showMessage("Showing "+QString::number(words_his.count())+" words from History.");
    ui_menu_widget->close();
    ui->listTypeLable->setText("Recent Search terms");
    hisLoaded = true;


    ui->listTypeLable->show();

    //in his
    if(hisLoaded){
             ui->listTypeLable->setVisible(true);
     }
    else {
         ui->listTypeLable->setVisible(false);
    }
}

void MainWindow::readHis(){
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) ;
    QFile file(path+"/history.txt");
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
              return;
    //QTextStream out(&file);

    QTextStream in(&file);
    words_his.clear();
    while(!in.atEnd()){
        words_his.append(file.readLine().trimmed());
    }
     readed_his = true;
}

void MainWindow::saveHis(){

    readHis();
    int tot =  words_his.count() ;
    int to_remove = tot - 200;
       if(words_his.count()>200){
         for(int i=0;i<to_remove;i++){
               words_his.removeAt(i);
         }
       }
      //now we have 200 latest words

    if(!words_his.contains(ui->fakeLineEdit->text().trimmed()+"#")&& !ui->fakeLineEdit->text().trimmed().isEmpty()){

        QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) ;
        QFile file(path+"/history.txt");
         if(!file.open(QIODevice::Truncate | QIODevice::ReadWrite| QIODevice::Text))
                  return;
        QTextStream out(&file);
        if(words_his.count()>0){
            esp ="\n";
        }else{
            esp.clear();
        }
// write words array
        for(int i=0;i<words_his.count();i++){
            if(!words_his.at(i).isEmpty())
                 out<<words_his.at(i)+"\n";
        }
// write new word
        out<<ui->fakeLineEdit->text().trimmed()+"#";
        file.close();
        readed_his = false;
 }
}

void MainWindow::on_lineEdit_editingFinished()
{
    //save history
    saveHis();
}

void MainWindow::clear_his_clicked()
{
    QMessageBox msgBox;
      msgBox.setText("Clear Recent Searched terms ?");
      msgBox.setIcon(QMessageBox::Information);
      msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Yes);
       int ret = msgBox.exec();
       switch (ret) {
       case QMessageBox::Yes:
               {QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) ;
               QFile file(path+"/history.txt");
                if(!file.open(QIODevice::Truncate | QIODevice::ReadWrite| QIODevice::Text))
                         return;
               QTextStream out(&file);
               out<<"";
               file.close();
               words_his.clear();
               showHis();}
           break;
       default:
           //showHis();
           break;
       }
}
