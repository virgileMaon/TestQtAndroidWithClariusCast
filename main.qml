import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: Screen.width > 1205 ? 1205 : Screen.width
    height: Screen.height !== 681 ? width * 681 / 1205 : Screen.height
    visible: true

    Rectangle {
        id: container
        anchors.fill: parent
        color: "gray"
        onColorChanged: console.log("color changed")
        ColumnLayout {
            id: colLifeCycle
            anchors.centerIn: parent

            property alias fromAnotherThread: chkAnotherThread.checked

            RowLayout {
                id: rowCreate
                onEnabledChanged: {
                    colLifeCycle.onCreateEnabled(enabled)
                    if (enabled) createStatus.text = "--"
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
                    width: btnCreate.width
                    height: btnCreate.height
                    color: root.getColor(createStatus.text)
                    Text {
                        id: createStatus
                        anchors.centerIn: parent
                        text: "--"
                        color: "black"
                    }
                }
                function create(anotherThread) {
                    if (cast_.create(anotherThread)) {
                        rowCreate.enabled = false
                        createStatus.text = "OK";
                    } else {
                        createStatus.text = "KO";
                    }
                }
            }
            RowLayout {
                id: rowRelease
                enabled: false
                onEnabledChanged: {
                    colLifeCycle.onReleaseEnabled(enabled)
                    if (enabled) releaseStatus.text = "--"
                }
                Button {
                    id: btnRelease
                    text: colLifeCycle.fromAnotherThread ? "Release Cast from another thread" : "Release Cast from UI thread"
                    onClicked: rowRelease.release()
                }
                Rectangle {
                    width: btnRelease.width
                    height: btnRelease.height
                    color: root.getColor(releaseStatus.text)
                    Text {
                        id: releaseStatus
                        anchors.centerIn: parent
                        text: "--"
                        color: "black"

                    }

                }
                function release() {
                    if (cast_.release()) {
                        rowRelease.enabled = false
                        releaseStatus.text = "OK";
                    } else {
                        releaseStatus.text = "KO";
                    }
                }

            }
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

        }
    }
    function getColor(txt) {
        if (txt === "--") return "gray"
        if (txt === "OK") return "green"
        if (txt === "KO") return "red"
    }
}
