#include "messagelistviewmodel.h"
#include <QDebug>
#include <simpletcpserver.h>


CMessageListViewModel::CMessageListViewModel()
{
    //m_LastActivePlayRowIdx = 0;
    m_iLastIndex = -1;
    CSimpleTcpServer *m_pSimpleTcpServer = new CSimpleTcpServer();

    connect(m_pSimpleTcpServer, SIGNAL(sigNewMessage(QString)), this, SLOT(slotNewMessage(QString)));
}

QVariant CMessageListViewModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
        return QVariant();
    const Data &data = m_data.at(index.row());

    if ( role == idx )
        return data.idx;
    else if ( role == text )
        return data.text;
    else if ( role == ownMessage )
        return data.ownMessage;
    else
        return QVariant();

}

int	CMessageListViewModel::rowCount(const QModelIndex &parent) const{
    if(parent.isValid())
        return 0;

    return m_data.count();
}

bool CMessageListViewModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "set data...";
    //int idx =  m_data[index.row()].idx;
    //bool playStatus = m_data[index.row()].playStatus;

    bool selected = m_data[index.row()].selected;

    /*QString keyValue = m_data[index.row()].keyValue;
    QString keyType = m_data[index.row()].keyType;

    if (index.isValid() && role == selectedRole) {
        if (selected != value.toBool()) {
            selected = m_data[index.row()].selected = value.toBool();
            return true;
        }
    }

    if (index.isValid() && role == keyTypeRole) {
        if (keyValue != value.toString()) {
            keyValue = m_data[index.row()].keyValue = value.toString();
            emit sigOnDataChanged(keyValue);
            return true;
        }
    }

    if (index.isValid() && role == keyValueRole) {
        if (keyType != value.toString()) {
            keyType = m_data[index.row()].keyType = value.toString();
            emit sigOnDataChanged(keyType);
            return true;
        }
    }*/



    return false;
}



void CMessageListViewModel::clearList(){
    beginResetModel();
    m_data.clear();
    endResetModel();
}

/**
 * @brief Method to add entries to the list. All QStringLists must have an equal lenght!!
 * If your visual representation needs less elements, simply pass one of your first elementse
 * multiple times.
 * @param l1
 * @param l2
 * @param l3
 * @param l4
 * @param l5
 * @param l6
 */
void CMessageListViewModel::slotOnListChanged(QStringList l1, QStringList l2){
    //qDebug() << QString("list changed. Entries:%1").arg(l1.size());

    beginResetModel();
    m_data.clear();


    /* Update list */
    for(int i=0; i<l1.size();i++){
        //m_data << Data(i,l1.at(i),l2.at(i));
    }

    /* Cut the end of the old list if larger */
    m_data.resize(l1.size());

    endResetModel();
}


/* Select and active a line by first entry */
void CMessageListViewModel::slotSelectEntryByEntry(QString entry)
{
    //int scrollPos;
    /*for(int i=0;i<m_data.size();i++){
        if(m_data.at(i).keyValue.contains(entry)){
            m_iLastIndex = -1; // force unselected state
            scrollPos = (i-6)*20; // We need to knew the current height of a line
            if(scrollPos>0) setScrollPos(scrollPos);
            onIndexChanged(i);
            return;
        }
    }*/

}

void CMessageListViewModel::slotUpdateList()
{
    beginResetModel();
    endResetModel();
}

void CMessageListViewModel::slotNewMessage(QString sMessage)
{
    qDebug() << sMessage;
    beginResetModel();
    Data newData;
    newData.ownMessage = false;
    newData.text = sMessage;
    m_data.append(newData);
    endResetModel();
}

/* From QML */
void CMessageListViewModel::onIndexChanged(int index){

    double dLastScrollPos = 0.0;
    qDebug() << "Search index changed... " << index;

    beginResetModel();
    dLastScrollPos = getScrollPos();
    if(m_iLastIndex>=0) m_data[m_iLastIndex].selected = false;
    m_data[index].selected = true;
    endResetModel();
    if(m_iLastIndex==index) emit sigOnLineSelected(index);
    m_iLastIndex = index;

    setScrollPos(dLastScrollPos);
}



/* New line hovered with mouse */
void CMessageListViewModel::onMouseOver(int index){
    emit sigOnMouseOver(index);

}

void CMessageListViewModel::appendLine(QString text, bool ownMessage)
{
    beginResetModel();
    Data newData;
    newData.text = text;
    newData.ownMessage = ownMessage;
    m_data.append(newData);
    endResetModel();
    qDebug() << "appending";
}

/* QML property callbacks */
double CMessageListViewModel::getScrollPos() const{ return m_scrollPos; }

void CMessageListViewModel::setScrollPos(double newScrollPos)
{
    m_scrollPos = newScrollPos;
    emit signalScrollPosChanged();
}

QVector<CMessageListViewModel::Data> *CMessageListViewModel::getListData()
{
    return &m_data;
}

void CMessageListViewModel::deleteLine(int lineIndex)
{
    beginResetModel();
    m_data.remove(lineIndex);
    endResetModel();
}
QHash<int, QByteArray> CMessageListViewModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[text] = "text";
    roles[ownMessage] = "ownMessage";
    return roles;
}







