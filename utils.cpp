#include "utils.h"

#include <QJsonParseError>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include <QVariantMap>

#include <QMessageBox>
namespace utils {

QVariantMap convertJsonResponse(const QByteArray &data)
{    
    QJsonParseError error;
    auto jsdoc = QJsonDocument::fromJson(data,&error);
    if ( error.error != QJsonParseError::NoError )
        qDebug() << "parse failed : " << error.errorString();

    //auto jsResponse = jsdoc.object()["response"].toObject();
    return jsdoc.object()["response"].toObject().toVariantMap();
}

}

