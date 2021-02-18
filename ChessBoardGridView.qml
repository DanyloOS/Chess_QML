import QtQuick 2.15

GridView {
    model: ChessCellsModel {

    }

    cellHeight: height / 8
    cellWidth: width / 8

    delegate: ChessCell {
        width: cellWidth
        height: cellHeight
        cellColor: colorRole
    }
}



//Rectangle {
//    property int offset: 0
//    x: (parent.x + offset)
//    y: (parent.y + offset)
//    width: parent.width - 2 * offset
//    height: parent.height - 2 * offset
//    color: "purple"
//    ChessCell {
//        id: a1
//        color: "#8b4513"
//    }
//    ChessCell {
//        id: a2
//        anchors.left: a1.right
//        color: "#ffdead"
//    }
//    ChessCell {
//        id: a3
//        anchors.left: a2.right
//        color: "#8b4513"
//    }
//    ChessCell {
//        id: a4
//        anchors.left: a3.right
//        color: "#ffdead"
//    }
//    ChessCell {
//        id: a5
//        anchors.left: a4.right
//        color: "#8b4513"
//    }
//    ChessCell {
//        id: a6
//        anchors.left: a5.right
//        color: "#ffdead"
//    }
//    ChessCell {
//        id: a7
//        anchors.left: a6.right
//        color: "#8b4513"
//    }
//    ChessCell {
//        id: a8
//        anchors.left: a7.right
//        color: "#ffdead"
//    }
//}
