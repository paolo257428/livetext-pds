#include "Client.h"


Client::Client(QObject* parent) : QObject(parent)
{
	socket = new QTcpSocket(this);

	connect(socket, SIGNAL(connected()), this, SLOT(serverConnection()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(serverDisconnection()));
	//connect(socket, SIGNAL(readyRead()), this, SLOT(readBuffer()));

	//socket->connectToHost("127.0.0.1", 1500);
}


Client::~Client()
{
	// TODO
}

void Client::writeOnServer()
{

}

void Client::serverConnection() {
	qDebug() << "Client connesso al server ";
	Login();
}

void Client::serverDisconnection() {
	qDebug() << "Client disconnesso dal server ";
}

void Client::readBuffer() {

	QByteArray responce = socket->read(256);
	qDebug() << responce;
}

bool Client::Login() {
	
	QDataStream out;
	quint16 typeOfMessage=0;

	out.setDevice(socket);

	out << typeOfMessage << username;

	QDataStream in;
	if (!socket->waitForReadyRead(10000)) {
		qDebug() << "recived no byte";
		//throw ServerNotRespondException();
		return false;
	}

	in.setDevice(socket);

	in >> typeOfMessage;

	switch (typeOfMessage) {
	case 1:
		break; 
	case 0:
		// user not exist
		qDebug() << "user not exists";
		return false;
		break;
	default:
		//throw MessageUnknownTypeException();
		return false;
		break;
	}

	
	QCryptographicHash hash(QCryptographicHash::Md5);

	QString salt;
	in >> salt;
	qDebug() << "cripting salt " << salt;
	password +=  salt;
	hash.addData(password.toStdString().c_str(), password.length());
	typeOfMessage = 2; 
	out << typeOfMessage << QString::fromStdString(hash.result().toStdString());
	in >> typeOfMessage;
	if (typeOfMessage == 3) {
		qDebug() << "access Granted";
		return true;
	}
	return false;
}

bool Client::Connect(QString ipAddress, quint16 port) {
	socket->connectToHost(ipAddress, port);
}

void Client::Disconnect() {
	socket->close();
	qDebug() << "connection closed by client";
}

void Client::setUsername(QString username) {

	this->username = username;

}
void Client::setPassword(QString password) {
	
	this->password = password;

}