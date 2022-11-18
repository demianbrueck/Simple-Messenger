import Felgo 3.0
import QtQuick 2.0
import QtQml.Models 2.3

App {
    // You get free licenseKeys from https://felgo.com/licenseKey
    // With a licenseKey you can:
    //  * Publish your games & apps for the app stores
    //  * Remove the Felgo Splash Screen or set a custom one (available with the Pro Licenses)
    //  * Add plugins to monetize, analyze & improve your apps (available with the Pro Licenses)
    //licenseKey: "<generate one from https://felgo.com/licenseKey>"

    NavigationStack {

        Page {
            title: qsTr("Messenger")
            backgroundColor: "white"
            AppListView{
                property int m_margin: 10
                id:idListView
                spacing: dp(m_margin)
                anchors.fill: parent
                anchors.topMargin: 10
                model: m_messageListModel
                scrollIndicatorVisible: false
                delegate: Rectangle{
                    anchors.right: model.ownMessage === true ? parent.right : undefined;
                    anchors.left: model.ownMessage === false ? parent.left : undefined;
                    anchors.rightMargin: model.ownMessage === true ? dp(idListView.m_margin) : undefined;
                    anchors.leftMargin: model.ownMessage === false ? dp(idListView.m_margin) : undefined;
                    width: childrenRect.width+dp(10)
                    height: childrenRect.height+dp(10)
                    color: model.ownMessage ? "deepskyblue" : "#E9E9EB"
                    radius:17
                    Text{
                        id:idText
                        text:model.text
                        color: model.ownMessage ? "white" : "black"
                        font.pixelSize: dp(20)
                        fontSizeMode : Text.HorizontalFit
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                }
                onCountChanged: {
                    var newIndex = count - 1 // last index
                    positionViewAtEnd()
                    currentIndex = newIndex
                }
            }

        }
    }

}

