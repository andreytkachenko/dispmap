import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600

    statusBar: StatusBar {
        Row {
            Label {
                id: statusBarState
                text: "In Progress"
            }
        }
    }

    Connections {
        target: processor
        onFinished: {
            statusBarState.text = "Ready";
        }
    }

    Item {
        anchors.fill: parent

        Item {
            id: leftColumn
            width: 200

            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.right: rightColumn.left
            anchors.left: parent.left

            Component {
                id: slider

                Item {
                    property alias title: sliderTitle.text
                    property alias from: sliderSlider.minimumValue
                    property alias to: sliderSlider.maximumValue
                    property alias step: sliderSlider.stepSize
                    property string name: ''

                    height: 50

                    Text {
                        id: sliderTitle
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.leftMargin: 15
                        anchors.rightMargin: 10
                        anchors.topMargin: 10
                        text: ""
                    }

                    Text {
                        id: sliderValue
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: sliderSlider.top
                        text: sliderSlider.value
                    }

                    Slider {
                        id: sliderSlider
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10
                        stepSize: 1
                    }
                }
            }

            Column {
                anchors.bottom: renderButton.top
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.left: parent.left

                Loader {
                    id: windowSize
                    sourceComponent: slider
                    anchors.left: parent.left
                    anchors.right: parent.right
                    onLoaded: {
                        windowSize.item.title = "Window Size"
                        windowSize.item.from = 0;
                        windowSize.item.to = 10;
                        windowSize.item.step = 1;
                    }
                }

                Loader {
                    id: matchSize
                    sourceComponent: slider
                    anchors.left: parent.left
                    anchors.right: parent.right
                    onLoaded: {
                        matchSize.item.title = "Match Size"
                        matchSize.item.from = 0;
                        matchSize.item.to = 10;
                        matchSize.item.step = 1;
                    }
                }

                Loader {
                    id: errorLevel
                    sourceComponent: slider
                    anchors.left: parent.left
                    anchors.right: parent.right
                    onLoaded: {
                        errorLevel.item.title = "Error Level"
                        errorLevel.item.from = 0;
                        errorLevel.item.to = 10;
                        errorLevel.item.step = 1;
                    }
                }
            }

            Button {
                id: renderButton
                //anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                Text {
                    anchors.centerIn: parent
                    text: "Render"
                }
            }
        }

        Item {
            id: rightColumn
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: leftColumn.right
            TabView {
                anchors.fill: parent
                Tab {
                    id: imageView
                    title: "Image View"
                    Item {
                        Flickable {
                            anchors.fill: parent
                            contentWidth: image.width
                            contentHeight: image.height
                            interactive: true
                            anchors.margins: 2
                            clip: true

                            Item {
                                Image {
                                    id: image
                                    source: ""
                                    smooth: false
                                }
                                Connections {
                                    target: processor
                                    onFinished: {
                                        image.source = "image://images/result";
                                    }
                                }
                            }
                        }
                    }
                }
                Tab {
                    id: pclView
                    title: "PCL View"

                    Item {
                        anchors.fill: parent
                    }
                }
            }
        }
    }
}
