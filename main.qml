import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Controls.Material

ApplicationWindow {
    id: root

    Material.accent: Material.Purple
    Material.theme: Material.Dark
    height: Qt.platform.os === "windows" ? 1140 : Screen.height
    visible: true
    width: Qt.platform.os === "windows" ? 540 : Screen.widht

    Component.onCompleted: {
        console.log(Screen.width, Screen.height);
    }

    Rectangle {
        anchors.fill: parent
        color: "#FFA500"
        visible: false
    }
    Item {
        anchors.fill: parent
        anchors.margins: 10

        Column {
            spacing: 10

            TextField {
                id: ip

                placeholderText: "IP address"
                text: "192.168.1.42"
            }
            TextField {
                id: port

                placeholderText: "TCP port"
                text: "5825"
            }
            TextField {
                id: networkId

                placeholderText: "Network ID"
                text: "578931314701"
            }
            Grid {
                columns: 1
                spacing: 10

                Button {
                    text: "CONNECT"

                    onClicked: {
                        console.log("connect");
                        cast_.connect(ip.text, parseInt(port.text), Number(networkId.text), "research");
                    }
                }
                Button {
                    text: "TOGGLE RUN"

                    onClicked: console.log("run")
                }
                Button {
                    text: "GET RAW DATA"

                    onClicked: console.log("get raw data")
                }
                Button {
                    text: "DISCONNECT"

                    onClicked: console.log("disconnect")
                }
                Button {
                    text: "CAPTURE IMAGE"

                    onClicked: console.log("capture image")
                }
            }
            Text {
                id: rez

                color: Material.accent
                text: cast_.result
            }
        }
    }
}

/*
import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts


ApplicationWindow {
    id: root

    function getColor(txt) {
        if (txt === "--")
            return "gray";
        if (txt === "OK")
            return "green";
        if (txt === "KO")
            return "red";
    }

    height: Screen.height// !== 681 ? width * 681 / 1205 : Screen.height
    visible: true
    width: Screen.width// > 1205 ? 1205 : Screen.width

    Rectangle {
        id: container

        anchors.fill: parent
        color: "gray"

        onColorChanged: console.log("color changed")

        ColumnLayout {
            id: colLifeCycle

            //anchors.centerIn: parent

            property alias fromAnotherThread: chkAnotherThread.checked

            function onCreateEnabled(enabled) {
                if (!enabled) {
                    rowRelease.enabled = true;
                }
            }
            function onReleaseEnabled(enabled) {
                if (!enabled) {
                    rowCreate.enabled = true;
                }
            }

            ColumnLayout {
                id: rowCreate

                function create(anotherThread) {
                    if (cast_.create(anotherThread)) {
                        rowCreate.enabled = false;
                        createStatus.text = "OK";
                    } else {
                        createStatus.text = "KO";
                    }
                }

                onEnabledChanged: {
                    colLifeCycle.onCreateEnabled(enabled);
                    if (enabled)
                        createStatus.text = "--";
                }

                Button {
                    id: btnCreate

                    text: colLifeCycle.fromAnotherThread ? "Construct Cast from another thread" : "Construct Cast from UI thread"

                    onClicked: rowCreate.create(chkAnotherThread.checked)
                }
                CheckBox {
                    id: chkAnotherThread

                    checked: false
                    text: "Invoked from another thread"
                }
                Rectangle {
                    color: root.getColor(createStatus.text)
                    height: btnCreate.height
                    width: btnCreate.width

                    Text {
                        id: createStatus

                        anchors.centerIn: parent
                        color: "black"
                        text: "--"
                    }
                }
            }
            ColumnLayout {
                id: rowRelease

                function release() {
                    if (cast_.release()) {
                        rowRelease.enabled = false;
                        releaseStatus.text = "OK";
                    } else {
                        releaseStatus.text = "KO";
                    }
                }

                enabled: false

                onEnabledChanged: {
                    colLifeCycle.onReleaseEnabled(enabled);
                    if (enabled)
                        releaseStatus.text = "--";
                }

                Button {
                    id: btnRelease

                    text: colLifeCycle.fromAnotherThread ? "Release Cast from another thread" : "Release Cast from UI thread"

                    onClicked: rowRelease.release()
                }
                Rectangle {
                    color: root.getColor(releaseStatus.text)
                    height: btnRelease.height
                    width: btnRelease.width

                    Text {
                        id: releaseStatus

                        anchors.centerIn: parent
                        color: "black"
                        text: "--"
                    }
                }
            }
        }
    }
}
*/
