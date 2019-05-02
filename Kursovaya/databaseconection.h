#ifndef DATABASECONECTION_H
#define DATABASECONECTION_H

#include <QSqlDatabase>


class DatabaseConection
{
public:
    DatabaseConection(const QString &server,
                     const QString &driver,
                      const QString &databaseName,
                      bool trustedConnection = true);
    bool openDatabase(QString *error = nullptr);
public:
    QSqlDatabase mDatabase;
    QString mServer;
    QString mDriver;
    QString mDataBaseName;
    bool mTrustedConnection;


};

#endif // DATABASECONECTION_H
