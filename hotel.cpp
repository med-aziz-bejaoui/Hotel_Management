#include "hotel.h"
#include "QDebug"

Hotel* Hotel::instance = nullptr;

int Hotel::CheckOut(int roomno)
{
    qDebug()<<"in CheckOut for room no : " << roomno;
    //**** update DB **********

    QSqlDatabase Database = QSqlDatabase::addDatabase("QSQLITE", "Data");
    Database.setDatabaseName("C:/Users/aziz/Desktop/Hotel_Management_in_QT/cppbuzz_hotelmanagement.db");
    if(QFile::exists("C:/Users/aziz/Desktop/Hotel_Management_in_QT/cppbuzz_hotelmanagement.db"))
        qDebug() << "DB file exist";
    else
       qDebug() << "DB file doesn't exists";

    if (!Database.open())
        qDebug() << Database.lastError().text();
    else
        qDebug() << "Database loaded successfull!";

    QSqlQuery query(Database);
    query.prepare("update cppbuzz_room set available ='y' where number='" +QString::number(roomno)+ "'");

    if(!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    else
        qDebug() << "Update was successful "<< query.lastQuery();


    Database.close();
    //getRoomList();
    return 0;
}

int Hotel::BookRoom(int roomno, QString name, QString contactno, QString govtid, QString address)
{
    qDebug() << "in BookRoom for room no : "<< roomno;

    //**** update DB **********

    QSqlDatabase Database = QSqlDatabase::addDatabase("QSQLITE", "Data");
    Database.setDatabaseName("C:/Users/aziz/Desktop/Hotel_Management_in_QT/cppbuzz_hotelmanagement.db");
    if(QFile::exists("C:/Users/aziz/Desktop/Hotel_Management_in_QT/cppbuzz_hotelmanagement.db"))
        qDebug() << "DB file exist";
    else
       qDebug() << "DB file doesn't exists";

    if (!Database.open())
        qDebug() << Database.lastError().text();
    else
        qDebug() << "Database loaded successfull!";

    QSqlQuery query(Database);

    //prepare hotel room query
    query.prepare("update cppbuzz_room set available ='n' where number='" +QString::number(roomno)+ "'");
    if(!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    else
        qDebug() << "Update was successful "<< query.lastQuery();

    //prepare customer query
    query.clear();
    query.prepare("insert into cppbuzz_customer (name, mobileno, govtid, address) values ('" + name + "','" + contactno + "','" + govtid + "','" + address + "')");
    QString customer_id;
    if(!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    else
    {
        qDebug() << "Update was successful "<< query.lastQuery();
        customer_id = query.lastInsertId().toString();
        qDebug() <<"Last Inserted Id is  : "<< customer_id;
    }

    //prepare transaction query
    query.clear();
    query.prepare("insert into cppbuzz_transaction (room, customer_id) values ('" + QString::number(roomno) + "','" + customer_id + "')");
    if(!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    else
    {
        qDebug() <<"Update was successful "<< query.lastQuery();
        qDebug() <<"Last Inserted Id is  : "<<query.lastInsertId().toString();
    }

    Database.close();
    //getRoomList();
    return 0;
}

std::vector<int> Hotel::getRoomList(QString flag = "y")
{
        std::vector<int> rooms;
        //if(availableRooms.empty())
        QSqlDatabase Database = QSqlDatabase::addDatabase("QSQLITE", "Data");
        Database.setDatabaseName("C:/Users/aziz/Desktop/Hotel_Management_in_QT/cppbuzz_hotelmanagement.db");
        if(QFile::exists("C:/Users/aziz/Desktop/Hotel_Management_in_QT/cppbuzz_hotelmanagement.db"))
            qDebug() << "DB file exist";
        else
           qDebug() << "DB file doesn't exists";

        if (!Database.open())
            qDebug() << Database.lastError().text();
        else
            qDebug() << "Database loaded successfull!";

        QSqlQuery query(Database);
        query.prepare("select number from cppbuzz_room where available = '" + flag + "'");

        if(!query.exec())
            qDebug() << query.lastError().text() << query.lastQuery();
        else
            qDebug() << "Fetch was successful";

        while(query.next())
        {
            QString record = query.value(0).toString();
            rooms.push_back(record.toInt());
            qDebug()<<"Line is : "<<record;
        }

        Database.close();
        return rooms;
}

Hotel *Hotel::getInstance()
{
    if(instance == nullptr)
        instance = new Hotel();
    return instance;
}
