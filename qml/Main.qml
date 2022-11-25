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
            useSafeArea: true
            title: qsTr("Messenger")
            backgroundColor: "white"
            AppListView{
                property int m_margin: 10
                id:idListView
                spacing: dp(m_margin)
                anchors{
                    left:parent.left
                    right:parent.right
                    bottom:idTextFieldRect.top
                    top:parent.top
                }
                anchors.topMargin: 10
                model: m_messageListModel
                scrollIndicatorVisible: false
                delegate: Rectangle{
                    anchors.right: model.ownMessage === true ? parent.right : undefined;
                    anchors.left: model.ownMessage === false ? parent.left : undefined;
                    anchors.rightMargin: model.ownMessage === true ? dp(idListView.m_margin) : undefined;
                    anchors.leftMargin: model.ownMessage === false ? dp(idListView.m_margin) : undefined;
                    width: idText.width+dp(10)
                    height: idText.height+dp(10)
                    color: model.ownMessage ? "deepskyblue" : "#E9E9EB"
                    radius:14
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
                    var newIndex = count - 1; // last index
                    positionViewAtEnd();
                    currentIndex = newIndex;
                }
            }
            Rectangle{
                id:idTextFieldRect
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                color:"darkgray"
                height: Theme.isAndroid ? Theme.statusBarHeight + dp(60) : dp(50)
                Rectangle{
                    height:dp(50)
                    color:"darkgray"
                    anchors{
                        bottom:parent.bottom
                        bottomMargin: Theme.isAndroid ? Theme.statusBarHeight + dp(10) : 0
                        left:parent.left
                        right:parent.right
                    }


                    Rectangle{
                        anchors{
                            left:parent.left
                            right: idSendButtonRect.left
                            bottom: parent.bottom
                            top:parent.top
                        }
                        color: "transparent"
                        Rectangle{
                            anchors{
                                left:parent.left
                                right: parent.right
                                bottom: parent.bottom
                                top:parent.top
                            }
                            color: "transparent"
                            AppTextField{
                                z:99
                                id:idTextField
                                anchors.fill:parent
                                anchors.leftMargin: dp(15)
                                backgroundColor: "transparent"
                                underlineColor: "transparent"
                            }
                            Rectangle{
                                anchors.margins: dp(5)
                                color:"white"
                                radius: dp(50)
                                anchors.fill: parent
                            }
                        }

                    }
                    Rectangle{
                        id:idSendButtonRect
                        width:height
                        radius: width*0.5
                        color:"white"
                        anchors{
                            margins: dp(5)
                            right:parent.right
                            top:parent.top
                            bottom:parent.bottom
                        }
                        MouseArea{
                            z:100
                            anchors.fill: parent
                            onClicked: {
                                if(idTextField.text != ""){
                                    m_messageListModel.appendLine(idTextField.text,true);
                                    m_simpleTcpServer.writeMessage(idTextField.text);
                                    idTextField.text = "";
                                }
                            }
                        }

                        Rectangle{
                            color:"darkgray"
                            radius: width*0.5
                            anchors.left:parent.left
                            anchors.right: parent.right
                            anchors.margins:dp(9)
                            height:dp(5)
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Rectangle{
                            color:"darkgray"
                            radius: width*0.5
                            anchors.top:parent.top
                            anchors.bottom: parent.bottom
                            anchors.margins:dp(9)
                            width:dp(5)
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }
            }

        }
    }

}

