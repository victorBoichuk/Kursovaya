#include "databaseconection.h"
#include <QSqlQuery>
#include <QSqlError>
DatabaseConection::DatabaseConection(const QString &server,
                                     const QString &driver,
                                      const QString &databaseName,
                                      bool trustedConnection)
{
    mDatabase = QSqlDatabase::addDatabase("QODBC");
    mServer = server;
    mDriver = driver;
    mDataBaseName = databaseName;
    mTrustedConnection = trustedConnection;

}

bool DatabaseConection::openDatabase( QString *error){
    mDatabase.setDatabaseName(QString("Driver={%1};SERVER=%2;DATABASE=%3; Trusted_Connection=%4;").arg(mDriver).arg(mServer).arg(mDataBaseName).arg(mTrustedConnection ? "YES":"NO"));
    if (!mDatabase.open()){
        if(error!=nullptr){
            *error=mDatabase.lastError().text();
        }
        return false;
    }
    return true;
}

