import QtQuick 2.5

MouseArea {
    id: root
    signal started()
    signal finsihed()
    signal moved(rect geometry)
    property Item piece

    property point __moveDelta: Qt.point(0, 0)

    cursorShape: pressed && active ? Qt.DragMoveCursor : Qt.ArrowCursor

    onPressed: {
        piece.focus = true
        started()
        var globalMousePos = mapToItem(null, mouse.x, mouse.y)
        var globalItemPos = mapToItem(null, root.x, root.y)
        __moveDelta = Qt.point(globalMousePos.x - globalItemPos.x,
                               globalMousePos.y - globalItemPos.y)
    }
    onPositionChanged: {
        var globalPos = mapToItem(null, mouse.x, mouse.y)
        var geometry = Qt.rect(globalPos.x - __moveDelta.x,
                               globalPos.y - __moveDelta.y,
                               piece.width, piece.height)
        moved(geometry)
    }
    onReleased: { finsihed() }
}
