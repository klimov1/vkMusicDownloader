#include "utils.h"

#include <QJsonParseError>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include <QVariantMap>

#include <QMessageBox>
namespace utils {

QVariantMap convertJson(const QByteArray &data)
{
    QMessageBox::critical(nullptr,"time to debug","debug");
    QJsonParseError error;
    auto jsdoc = QJsonDocument::fromJson(data,&error);
    if ( error.error != QJsonParseError::NoError )
        qDebug() << "parse failed : " << error.errorString();

    auto jsResponse = jsdoc.object()["response"].toObject();
    qDebug() << jsResponse;
    return jsResponse.toVariantMap();
}

}

