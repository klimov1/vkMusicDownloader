#include "utils.h"

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QDebug>

namespace utils {

QVariantMap convertJsonResponse(const QByteArray &data)
{    
    QJsonParseError error;
    auto jsdoc = QJsonDocument::fromJson(data, &error);
    if ( error.error != QJsonParseError::NoError )
    {
        qDebug() << "Parse failed : " + error.errorString();
        throw std::runtime_error("Unable to parse json. Check logs for info.");
    }

    return jsdoc.object()["response"].toObject().toVariantMap();
}

}
