#include "widget.h"
#include "ui_widget.h"

#include "request.h"

#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVector>
#include <QFile>


const QString CONFIG_FILE = "config.txt";

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
/*
    connect(ui->songCountEdit_, SIGNAL(textChanged()),[&](const QString& str){
        songCount_ = str.toInt();
    });
/*    connect(ui->webView, SIGNAL(urlChanged(QUrl)), this, SLOT(checkUrl(QUrl)) );
    connect(this, SIGNAL(authSuccess()),this, SLOT(getFriends()));

    qDebug() << "read token";
    readToken();

    if (token_.isEmpty())
    {
        ui->webView->load(QUrl("https://oauth.vk.com/authorize?client_id=5453408&redirect_uri=https://oauth.vk.com/blank.html&scope=offline,messages,friends&display=wap&response_type=token"));
        ui->label->clear();
    }
    else
        emit authSuccess();*/
}

Widget::~Widget()
{
    delete ui;
}

void Widget::checkUrl(QUrl url)
{
/*    qDebug() << url.toString();

    url = url.toString().replace("#","?");

    token_ = QUrlQuery(url).queryItemValue("access_token");

    if ( token_.isEmpty() )
        return;

    ui->label->setText("Success. Token : " + token_);
    saveToken();
    qDebug() << "authSuccess";
    emit authSuccess();*/
}

void Widget::getFriends()
{
  /*  qDebug() << "getFriends";

    auto request = request::create(request::urlFriendsGet,
                   { {"v","5.8"},
                     {"fields","first_name,last_name"},
                     {"access_token", token_} } );

    auto answer = GET( request );
    if ( answer.isEmpty() )
    {
        qDebug() << "Empty answer";
        exit(-1);
    }

    QJsonParseError error;
    auto jsdoc = QJsonDocument::fromJson(answer,&error);
    if ( error.error != QJsonParseError::NoError )
        qDebug() << "parse failed : " << error.errorString();

    auto jsResponse = jsdoc.object()["response"].toObject();

    //qDebug() << jsResponse.toVariantMap();

    int friendsCount = jsResponse["count"].toInt();
    qDebug() << "FriendCount " <<  friendsCount;

    QJsonArray friendsArray = jsResponse["items"].toArray();

    //qDebug() << friendsArray;

    QVector<User> friends;
    for( auto it : friendsArray)
    {
        User user;
        auto friendObj = it.toObject();
        //qDebug() << friendObj;
        //qDebug() << friendObj["id"].toDouble() << " " << friendObj["first_name"].toString();

        user.id_ = static_cast<qlonglong>( friendObj.take("id").toDouble() );
        user.firstName_ = friendObj.take("first_name").toString();
        user.lastName_ = friendObj.take("last_name").toString();
        user.isOnline_ = static_cast<bool>( friendObj.take("online").toInt() );

        friends.push_back(user);
    }

    qDebug() << "online users count " << friends.size();
    for ( auto& it : friends )
    {
        if ( it.isOnline_ )
            qDebug() << it.id_ << " " << it.firstName_ << " " << it.lastName_ << " "<< it.isOnline_;
    }*/
}

QByteArray Widget::GET(QUrl url)
{
   /* QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkReply* reply = manager->get(QNetworkRequest( url ));
    QEventLoop wait;
    connect(manager, SIGNAL(finished(QNetworkReply*)),&wait,SLOT(quit()));
    connect(manager, SIGNAL(finished(QNetworkReply*)),&wait,SLOT(deleteLater()));
    QTimer::singleShot(10000,&wait,SLOT(quit()));

    wait.exec();

    QByteArray answer = reply->readAll();
    reply->deleteLater();*/

    return QByteArray();
}

void Widget::saveToken()
{
    /*QFile file(CONFIG_FILE);
    file.open(QFile::WriteOnly);
    //file.cr
    if (!file.isOpen()){
        qDebug() << "Unable to open file";
        return;
    }

    qDebug() << "try to write " << QByteArray::fromStdString(token_.toStdString()) << " to file " << file.fileName();

    file.write(QByteArray::fromStdString(token_.toStdString()));
    */
}

void Widget::readToken()
{
  /*  QFile file(CONFIG_FILE);
    file.open(QFile::ReadOnly);
    if (!file.isOpen()){
        qDebug() << "Unable to open file";
        return;
    }

    token_ = file.readAll();
    qDebug() << "read token " << token_;*/
}

#include "audio.h"
#include "config.h"


void Widget::on_getAudiosBtn_clicked()
{


    auto songsList = audio::getSongs(Config::getInstance().getUserId());

        for ( auto& it : songsList )
            qDebug() << it.artist_ << " - " << it.title_ << " : " << it.duration_;
}
