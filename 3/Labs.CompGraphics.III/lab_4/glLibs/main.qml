import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.11
import opengl_lib 1.0

Item {
    width: 640
    height: 480
    visible: true

    QuickItem {
        id: item
        anchors.fill: parent
//        Column {
//            spacing: 5
//            anchors.left: parent.left
//            anchors.leftMargin: 10
//            Item { width: 1; height: 10 }
//            Row {
//                id: lightPos_1
//                spacing: 10
//                Label { text: "X1"; color: "white" }
//                TextField { id: x_1; width: 40; height: 20 }
//                Label { text: "Y1"; color: "white" }
//                TextField { id: y_1; width: 40; height: 20 }
//                Label { text: "Z1"; color: "white" }
//                TextField { id: z_1; width: 40; height: 20 }
//                Button { width: 100; height: 20; text: "Применить"; onClicked: item.light_1.setPosition(x_1.text, y_1.text, z_1.text) }
//            }
//            Row {
//                id: lightPos_2
//                spacing: 10
//                Label { text: "X2"; color: "white" }
//                TextField { id: x_2; width: 40; height: 20 }
//                Label { text: "Y2"; color: "white" }
//                TextField { id: y_2; width: 40; height: 20 }
//                Label { text: "Z2"; color: "white" }
//                TextField { id: z_2; width: 40; height: 20 }
//                Button { width: 100; height: 20; text: "Применить"; onClicked: item.light_2.setPosition(x_2.text, y_2.text, z_2.text) }
//            }
//            Row {
//                id: lightPos_3
//                spacing: 10
//                Label { text: "X3"; color: "white" }
//                TextField { id: x_3; width: 40; height: 20 }
//                Label { text: "Y3"; color: "white" }
//                TextField { id: y_3; width: 40; height: 20 }
//                Label { text: "Z3"; color: "white" }
//                TextField { id: z_3; width: 40; height: 20 }
//                Button { width: 100; height: 20; text: "Применить"; onClicked: item.light_3.setPosition(x_3.text, y_3.text, z_3.text) }
//            }
//            Row {
//                id: lightColor_1
//                spacing: 10
//                Label { text: "light color 1"; color: "white" }
//                TextField { id: r_1; width: 100; height: 20 }
//                Button { width: 100; height: 20; text: "Применить"; onClicked: item.light_1.color = r_1.text }
//            }
//            Row {
//                id: lightColor_2
//                spacing: 10
//                Label { text: "light color 2"; color: "white" }
//                TextField { id: r_2; width: 100; height: 20 }
//                Button { width: 100; height: 20; text: "Применить"; onClicked: item.light_2.color = r_2.text }
//            }
//            Row {
//                id: lightColor_3
//                spacing: 10
//                Label { text: "light color 3"; color: "white" }
//                TextField { id: r_3; width: 100; height: 20 }
//                Button { width: 100; height: 20; text: "Применить"; onClicked: item.light_3.color = r_3.text }
//            }
//            Row {
//                id: objectColor
//                spacing: 10
//                Label { text: "object color"; color: "white" }
//                TextField { id: colorTxt; width: 100; height: 20 }
//                Button { width: 100; height: 20; text: "Применить"; onClicked: item.objectColor = colorTxt.text }
//            }
//            Row {
//                Label { text: "Specular strength:"; color: "white" }
//                Slider {
//                    id: specStrength
//                    from: 0
//                    to: 256
//                    value: 32
//                    onValueChanged: item.specStrength = value
//                }
//            }
//            Row {
//                Label { text: "Specular intencity:"; color: "white" }
//                Slider {
//                    id: intensity
//                    from: 0
//                    to: 5
//                    value: 0.5
//                    onValueChanged: item.specIntensity = value
//                }
//            }
//        }
    }
}
