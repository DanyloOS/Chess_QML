import QtQuick 2.15

Rectangle {
    color: "black"
    ChessBoardGridView {
        property int offset: 30
        anchors.fill: parent
        anchors.margins: offset
        width: parent.width - 2 * offset
        height: parent.height - 2 * offset
        Image {
            width: parent.width / 8
            height: width
            id: kingWhite
//            anchors.left:
            source: "chess_pieces_1.png"
            sourceClipRect: Qt.rect(0, 0, 200, 200)
        }
        Image {
            width: parent.width / 8
            height: width
            id: kingBlack
//            anchors.left: ChessBoardGridView.left
            source: "chess_pieces_1.png"
            sourceClipRect: Qt.rect(0, 200, 200, 200)
        }
    }
}
