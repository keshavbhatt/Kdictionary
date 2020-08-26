#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QByteArray>
#include <QCheckBox>
#include <QDebug>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QDialog>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QHotkey>
#include <QKeySequence>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QMouseEvent>
#include <QProcess>
#include <QtNetwork>

#include <QSettings>
#include <QSplitter>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>

#include <QStandardPaths>
#include <QSystemTrayIcon>
#include <QTextBlock>
#include <QTextCodec>

#include <QTimer>
#include <QWebFrame>
#include <QWebInspector>
#include <QWebPage>

#include <QRegExp>

#include "ui_menu.h"
#include "ui_instant_result.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Q_INVOKABLE void get_voices(QVariant);
    Q_INVOKABLE QString get_selectedVoice();

    ~MainWindow();

private slots:
       void request_done();
       void online_search(QString , QString);

    void mousePressEvent(QMouseEvent *evt);

    void mouseMoveEvent(QMouseEvent *evt);

    void mouseDoubleClickEvent(QMouseEvent *evt);

    void setStyle(QString fname);

    void on_pushButton_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

    void query_word(QString , int i);

    void show_meaning(QString , QSqlQuery ,bool);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_returnPressed();

    void on_close_btn_clicked();
    void on_max_btn_clicked();
    void on_min_btn_clicked();

    void language_changed(int);

    void kdictView_progress(int);

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_tabWidget_currentChanged(int index);

    void on_wiktionaryPushButton_clicked();

    void on_read_textPushBtn_clicked();

//  void pronouncePermission(QWebFrame *frame, QWebPage::Feature feature);

    void on_read_DefinitionPushBtn_clicked();

    void on_read_abovePushBtn_clicked();

    void on_kdictSearchBtn_clicked();

    void kdictView_loaded(bool);

    void on_wikipedia_searchBtn_clicked();

    void wikiWebView_progress(int);

    void wikiWebView_loaded(bool);


    void on_imageSearchBtn_clicked();

    void images_request_done();

    void closeEvent(QCloseEvent *event);

    void readSettings();

    void init_webviews();

    void imageView_progress(int);

    void on_imageSearchLineEdit_returnPressed();

    void on_wiktionaryLineEdit_returnPressed();

    void on_Wikipedia_searchLineEdit_returnPressed();

    void on_kdictLineEdit_returnPressed();

    void on_dictCombo_currentIndexChanged(int index);



    void on_stop_reading_PushBtn_clicked();

    void on_pausePushBtn_clicked();

    void on_resumePushBtn_2_clicked();


    void on_voiceList_currentIndexChanged(const QString &arg1);

    void show_requested_word();
    void get_selected_word_fromX11();
    void set_x11_selection();

    bool eventFilter(QObject *obj, QEvent *event);

    void textSelectionChanged();
    void textBrowser_2_selectionChanged();
    void wikiWebViewSelectionChnaged();
    void kdictWebViewSelectionChnaged();

    void on_kdictLineEdit_textChanged(const QString &arg1);

    void on_Wikipedia_searchLineEdit_textChanged(const QString &arg1);

    void on_wiktionaryLineEdit_textChanged(const QString &arg1);

    void on_imageSearchLineEdit_textChanged(const QString &arg1);


    void evaluateClickedLink_in_kdictWebPage(QUrl);

    void init_main_menu();

    void init_instant_result();

    void on_menu_clicked();

    void ask_word_net(bool);

    void on_wordnetSearchBtn_clicked();

    void show_wn_result(int ); //wn offline

    void on_wordnetsearchLineEdit_textChanged(const QString &arg1);

    void process_wn_output(QString);

    void on_grepCombo_currentIndexChanged(const QString &arg1);

    void on_wordnetTextBrowser_cursorPositionChanged();

    void show_MainWindow();

    void liveSearchcheckBoxToggled(bool);

    void bottomPanelCheckBoxToggled(bool);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void setShortcut(const QKeySequence &sequence);

    void on_wordnetsearchLineEdit_returnPressed();


    void wordnetTextBrowserSelectionChanged();

    void on_favurite_btn_clicked();

    void check_fav();

    void add_fav();

    void rem_fav();

    void read_favFile();

    void showFav();

    void on_fakeLineEdit_textChanged(const QString &arg1);

    void showHis();

    void readHis();
    void saveHis();

    void on_lineEdit_editingFinished();

    void clear_his_clicked();

    void show_SysTrayIcon();

    void check_window_state();

    void minimizeApp_in_tray(bool);

    QString shortCut_set_check_return();

    void show_net_error_message(bool b);

    void open_website();

private:
    QSettings settings;
    QPoint oldPos;
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QStringList dicts;


    QHotkey *nativeHotkey;
    QString voiceType ,btn_style;
    QStringList lang_codes;

    QNetworkReply *reply ,*images_reply, *update_reply;
    QNetworkAccessManager m_network_manager;

    QString x11_selected,wn_result, word_for_image_search;

    Ui::menu ui_menu;
    QWidget *ui_menu_widget;

    Ui::instant_result ui_instant_result;
    QWidget *instant_result_widget;
    bool asked_by_instant_result;

    QStringList words_fav, words_his;

    QString esp;

    bool isFav,readed_fav,favLoaded,readed_his,hisLoaded;

    bool showMsgBox;

};

#endif // MAINWINDOW_H
