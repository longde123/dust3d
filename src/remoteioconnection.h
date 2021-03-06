#ifndef REMOTE_IO_CONNECTION_H
#define REMOTE_IO_CONNECTION_H
#include <QObject>
#include <QTcpSocket>
#include <vector>
#include <QByteArray>
#include <map>
#include <QList>
#include "documentwindow.h"

class RemoteIoConnection;
using CommandHandler = std::function<QByteArray(RemoteIoConnection *, const QByteArray&, QString *)>;

class RemoteIoConnection : QObject
{
    Q_OBJECT

public:
    explicit RemoteIoConnection(QTcpSocket *tcpSocket);
    ~RemoteIoConnection();
    
private slots:
    void handleRead();

private:
    QTcpSocket *m_tcpSocket = nullptr;
    QByteArray m_receiveCache;
    DocumentWindow *m_currentDocumentWindow = nullptr;
    std::map<QString, CommandHandler> m_commandHandlers;
    QList<QMetaObject::Connection> m_documentConnections;
    
    QByteArray nextCommandFromCache();
    QString nameFromCommand(const QByteArray &command, int *parametersBegin=nullptr);
    QString nextParameter(const QByteArray &parameters, int *offset);
    bool isWhitespace(char c);
    void connectDocumentSignals();
    void disconnectDocumentSignals();
    void connectDocumentWindow(DocumentWindow *window);
    void respondEventWithId(const QString &eventName, const QUuid &id);
    void respondEvent(const QString &eventName);
    
    QByteArray commandListWindow(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSelectWindow(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandUndo(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandRedo(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandPaste(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandRemoveNode(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandRemoveEdge(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandRemovePart(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandAddNode(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandAddNodeWithId(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandScaleNodeByAddRadius(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandMoveNodeBy(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSetNodeOrigin(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSetNodeRadius(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSetNodeBoneMark(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSwitchNodeXZ(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandMoveOriginBy(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandAddEdge(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSetPartLockState(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSetPartVisibleState(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSetPartSubdivState(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSetPartDisableState(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSetPartXmirrorState(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSetPartRoundState(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSetPartChamferState(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandGetNodePartId(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSaveSnapshot(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandGetSnapshot(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandExportAsObj(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandNew(const QByteArray &parameters, QString *errorMessage);
    QByteArray commandSetPartColor(const QByteArray &parameters, QString *errorMessage);
};

#endif

