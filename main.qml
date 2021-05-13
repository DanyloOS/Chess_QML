import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 640
    title: qsTr("GNU Chess")


    GameBoard {
        id: gameBoard
        anchors.centerIn: parent
        property int boardSize: Math.min(parent.width, parent.height)
        width: boardSize
        height: boardSize
        anchors.margins: 20
    }

    Page {
        id: resultPage
        anchors.fill: parent
        visible: false

        background: Rectangle {
            id: backgroundRect
            anchors.fill: resultPage
            opacity: 0.4
            color: "grey"

            MouseArea {
                anchors.fill: parent
            }
        }

        Rectangle {
            color: "lightsalmon"
            opacity: 0.8
            width:  gameBoard.boardSize * 0.5
            height: width * 0.5
            radius: 20
            anchors.centerIn: parent

            Column {
                anchors.fill: parent
                spacing: height * 0.1
                Rectangle {
                    width: parent.width
                    height: parent.height * 0.4
                    anchors.topMargin: parent.height * 0.05
                    color: "transparent"
                    Text {
                        id: resultText
                        property int playerInt: 0
                        anchors.centerIn: parent
                        font.family: "ComicSans"
                        font.pointSize: parent.width / 20
                        text: {
                            var player = (playerInt === 1) ? "White" : "Black"
                            if (playerInt === -1) return "Draw"
                            else return player + " won!"
                       }
                    }
                }

                RoundButton {
                    width: parent.width * 0.8
                    height: parent.height * 0.4
                    anchors.bottomMargin: parent.height * 0.05
                    anchors.horizontalCenter: parent.horizontalCenter
                    radius: 20
                    font.family: "ComicSans"
                    font.pointSize: width / 12
                    text: "RESTART"

                    onClicked: {
                        resultPage.visible = false
                        chessBoardModel.resetModel();
                    }
                }

            }
            Connections {
                target: chessBoardModel
                function onWinnerChanged(pieceColor) {
                    console.log("Hello from here")
                    console.log(pieceColor)
                    resultText.playerInt = pieceColor
                    resultPage.visible = true
                }
            }
        }
    }
}
