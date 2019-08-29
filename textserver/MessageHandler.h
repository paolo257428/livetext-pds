#pragma once

#include <QObject>
#include <QTcpSocket>

#include <Message.h>
#include <User.h>
#include "Document.h"


class WorkSpace;
class TcpServer;

class MessageHandler : public QObject
{
	Q_OBJECT

private:

	enum OwnerType
	{
		Server,
		Workspace
	};

private:

	OwnerType _usecase;

public:

	MessageHandler(WorkSpace* w);
	MessageHandler(TcpServer* s);

	void process(MessageCapsule message, QTcpSocket* sender);

	~MessageHandler();


signals: MessageCapsule loginRequest(QTcpSocket* clientSocket, QString username);
signals: MessageCapsule loginUnlock(QTcpSocket* clientSocket, QString token);

signals: MessageCapsule accountCreate(QTcpSocket* ÁlientSocket, User& newUser);
signals: MessageCapsule accountUpdate(QTcpSocket* ÁlientSocket, User& updatedUser);

signals: MessageCapsule documentCreate(QTcpSocket* ÁlientSocket, QString docName);
signals: MessageCapsule documentOpen(QTcpSocket* ÁlientSocket, URI docUri);
signals: MessageCapsule documentRemove(QTcpSocket* ÁlientSocket, URI docUri);

signals: void charInsert(Symbol& s);
signals: void charDelete(QVector<qint32> pos);
signals: void messageDispatch(MessageCapsule message, QTcpSocket* sender);

signals: void removePresence(QTcpSocket* clientSocket);
signals: void userLogout(QTcpSocket* clientSocket);

};
