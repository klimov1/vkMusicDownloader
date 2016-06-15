#include "widget.h"
#include "ui_widget.h"

#include "request.h"
#include "audio.h"
#include "config.h"

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

    QIntValidator* validator = new QIntValidator(0, 3000, this);
    ui->songCountEdit->setValidator(validator);
    connect(ui->songCountEdit,SIGNAL(textChanged(QString)),this,SLOT(songCountChanged(QString)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::songCountChanged(QString text)
{
    songCount_ = text.toInt();
}

void Widget::on_getAudiosBtn_clicked()
{
    auto songsList = audio::getSongs(Config::getInstance().getUserId(), static_cast<std::size_t>(songCount_));
    for ( auto& it : songsList )
        qDebug() << it.artist_ << " - " << it.title_ << " : " << it.duration_;
}


