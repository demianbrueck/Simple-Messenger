#ifndef CLISTVIEWMODEL_H
#define CLISTVIEWMODEL_H


#include <QAbstractListModel>
#include <QObject>
#include <QFileDialog>
#include <QMessageBox>
#include <QTime>
#include <QTextStream>


class CMessageListViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        idx = Qt::UserRole + 1,
        selectedRole,
        text,
        ownMessage
    };

    struct Data{
        Data(){}
        Data(int idx,const QString& text, const bool& ownMessage) :
            idx(idx),text(text), ownMessage(ownMessage){}
        int idx;
        int selected;
        QString text;
        bool ownMessage;
    };




private:
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int	rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

    //int m_LastActivePlayRowIdx;
    int m_iLastIndex;

    QVector <Data> m_data;
    double m_scrollPos;


public:
    CMessageListViewModel();
    void clearList();

    Q_INVOKABLE void onIndexChanged(int index);
    Q_INVOKABLE void onMouseOver(int index);
    Q_INVOKABLE void appendLine(QString text,bool ownMessage);
    Q_INVOKABLE void deleteLine(int lineIndex);

    double getScrollPos() const;
    void setScrollPos(double newScrollPos);
    QVector <Data> * getListData();

signals:
    /*-- class signals -- */
    void sigOnDataChanged(QString text);
    void sigOnLineSelected(int index);
    void sigOnMouseOver(int index);
    void signalScrollPosChanged();

public slots:
    void slotOnListChanged(QStringList l1, QStringList l2);
    void slotSelectEntryByEntry(QString entry);
    void slotUpdateList();

};

#endif // CLISTVIEWMODEL_H

