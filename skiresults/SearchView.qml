import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.2

Item
{
    width: parent.width
    height: parent.height - 250
    id: root
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    states: [
        State {
            name: "1"
            PropertyChanges {
                target: year1;
                visible: true
            }
            PropertyChanges {
                target: year2;
                visible: false
            }
            PropertyChanges {
                target: starttime;
                visible: true
            }
            PropertyChanges {
                target: endttime;
                visible: true
            }
            PropertyChanges {
                target: racetag1;
                visible: true
            }
            PropertyChanges {
                target: racetag2;
                visible: false
            }
            PropertyChanges {
                target: athletename;
                visible: false
            }
            PropertyChanges {
                target: sizeofranking;
                visible: false
            }
            PropertyChanges {
                target: gender;
                visible: false
            }
        },
        State {
            name: "2"
            PropertyChanges {
                target: year1;
                visible: true
            }
            PropertyChanges {
                target: year2;
                visible: true
            }
            PropertyChanges {
                target: starttime;
                visible: false
            }
            PropertyChanges {
                target: endttime;
                visible: false
            }
            PropertyChanges {
                target: racetag1;
                visible: true
            }
            PropertyChanges {
                target: racetag2;
                visible: false
            }
            PropertyChanges {
                target: athletename;
                visible: false
            }
            PropertyChanges {
                target: sizeofranking;
                visible: true
            }
            PropertyChanges {
                target: gender;
                visible: false
            }
        },
        State {
            name: "3"
            PropertyChanges {
                target: year1;
                visible: true
            }
            PropertyChanges {
                target: year2;
                visible: false
            }
            PropertyChanges {
                target: starttime;
                visible: false
            }
            PropertyChanges {
                target: endttime;
                visible: false
            }
            PropertyChanges {
                target: racetag1;
                visible: true
            }
            PropertyChanges {
                target: racetag2;
                visible: true
            }
            PropertyChanges {
                target: athletename;
                visible: false
            }
            PropertyChanges {
                target: sizeofranking;
                visible: false
            }
            PropertyChanges {
                target: gender;
                visible: false
            }
        },
        State {
            name: "4"
            PropertyChanges {
                target: year1;
                visible: false
            }
            PropertyChanges {
                target: year2;
                visible: false
            }
            PropertyChanges {
                target: starttime;
                visible: false
            }
            PropertyChanges {
                target: endttime;
                visible: false
            }
            PropertyChanges {
                target: racetag1;
                visible: false
            }
            PropertyChanges {
                target: racetag2;
                visible: false
            }
            PropertyChanges {
                target: athletename;
                visible: false
            }
            PropertyChanges {
                target: sizeofranking;
                visible: false
            }
            PropertyChanges {
                target: gender;
                visible: false
            }
        },
        State {
            name: "5"
            PropertyChanges {
                target: year1;
                visible: true
            }
            PropertyChanges {
                target: year2;
                visible: true
            }
            PropertyChanges {
                target: starttime;
                visible: false
            }
            PropertyChanges {
                target: endttime;
                visible: false
            }
            PropertyChanges {
                target: racetag1;
                visible: false
            }
            PropertyChanges {
                target: racetag2;
                visible: false
            }
            PropertyChanges {
                target: athletename;
                visible: true
            }
            PropertyChanges {
                target: sizeofranking;
                visible: false
            }
            PropertyChanges {
                target: gender;
                visible: false
            }
        },
        State {
            name: "6"
            PropertyChanges {
                target: year1;
                visible: true
            }
            PropertyChanges {
                target: year2;
                visible: true
            }
            PropertyChanges {
                target: starttime;
                visible: false
            }
            PropertyChanges {
                target: endttime;
                visible: false
            }
            PropertyChanges {
                target: racetag1;
                visible: true
            }
            PropertyChanges {
                target: racetag2;
                visible: false
            }
            PropertyChanges {
                target: athletename;
                visible: false
            }
            PropertyChanges {
                target: sizeofranking;
                visible: true
            }
            PropertyChanges {
                target: gender;
                visible: false
            }
        },
        State {
            name: "7"
            PropertyChanges {
                target: year1;
                visible: true
            }
            PropertyChanges {
                target: year2;
                visible: true
            }
            PropertyChanges {
                target: starttime;
                visible: false
            }
            PropertyChanges {
                target: endttime;
                visible: false
            }
            PropertyChanges {
                target: racetag1;
                visible: true
            }
            PropertyChanges {
                target: racetag2;
                visible: false
            }
            PropertyChanges {
                target: athletename;
                visible: false
            }
            PropertyChanges {
                target: sizeofranking;
                visible: false
            }
            PropertyChanges {
                target: gender;
                visible: true
            }
        },
        State {
            name: "8"
            PropertyChanges {
                target: year1;
                visible: true
            }
            PropertyChanges {
                target: year2;
                visible: false
            }
            PropertyChanges {
                target: starttime;
                visible: false
            }
            PropertyChanges {
                target: endttime;
                visible: false
            }
            PropertyChanges {
                target: racetag1;
                visible: false
            }
            PropertyChanges {
                target: racetag2;
                visible: false
            }
            PropertyChanges {
                target: athletename;
                visible: false
            }
            PropertyChanges {
                target: sizeofranking;
                visible: false
            }
            PropertyChanges {
                target: gender;
                visible: false
            }
        },
        State {
            name: "9"
            PropertyChanges {
                target: year1;
                visible: false
            }
            PropertyChanges {
                target: year2;
                visible: false
            }
            PropertyChanges {
                target: starttime;
                visible: false
            }
            PropertyChanges {
                target: endttime;
                visible: false
            }
            PropertyChanges {
                target: racetag1;
                visible: false
            }
            PropertyChanges {
                target: racetag2;
                visible: false
            }
            PropertyChanges {
                target: athletename;
                visible: false
            }
            PropertyChanges {
                target: sizeofranking;
                visible: false
            }
            PropertyChanges {
                target: gender;
                visible: false
            }
        },
        State {
            name: "10"
            PropertyChanges {
                target: year1;
                visible: true
            }
            PropertyChanges {
                target: year2;
                visible: false
            }
            PropertyChanges {
                target: starttime;
                visible: false
            }
            PropertyChanges {
                target: endttime;
                visible: false
            }
            PropertyChanges {
                target: racetag1;
                visible: true
            }
            PropertyChanges {
                target: racetag2;
                visible: false
            }
            PropertyChanges {
                target: athletename;
                visible: false
            }
            PropertyChanges {
                target: sizeofranking;
                visible: false
            }
            PropertyChanges {
                target: gender;
                visible: false
            }
        }
    ]

    Column{

        anchors.horizontalCenter: parent.horizontalCenter

        Column
        {
            spacing: 20
            Row
            {
                spacing: 20
                ComboBox {
                    currentIndex: 1
                    model: ListModel {
                        id: choiceItems
                        ListElement { text: "read by time"; name: "1" }
                        ListElement { text: "compare result by year"; name: "2" }
                        ListElement { text: "compare distance by year"; name: "3" }
                        ListElement { text: "show stats by each year"; name: "4" }
                        ListElement { text: "athlete time development"; name: "5" }
                        ListElement { text: "average speed by ranking"; name: "6" }
                        ListElement { text: "best athlete by gender in period"; name: "7" }
                        ListElement { text: "show sorted results by club name"; name: "8" }
                        ListElement { text: "show athlete distribution by country"; name: "9" }
                        ListElement { text: "show ten best teams"; name: "10" }
                    }
                    width: 200
                    onCurrentIndexChanged: root.state = choiceItems.get(currentIndex).name
                }

                Column
                {
                    spacing: 20
                    Row
                    {
                        spacing: 20
                        Column
                        {
                            id: year1
                            spacing: 10
                            property string name: "Year 1"
                            function getText()
                            {
                                return combo1.currentText;
                            }
                            Text
                            {
                                text: "Year 1"
                            }
                            ComboBox
                            {
                                id: combo1
                                model: yearsModel
                                onActivated: {
                                    controller.setNewRaceTags(root.state, year1.getText(), year2.getText())
                                }
                            }
                        }


                        Column
                        {
                            id: year2
                            spacing: 10
                            property string name: "Year 2"
                            function getText()
                            {
                                return combo2.currentText;
                            }
                            Text
                            {
                                text: "Year 1"
                            }
                            ComboBox
                            {
                                id: combo2
                                model: yearsModel
                                onActivated: {
                                    controller.setNewRaceTags(root.state, year1.getText(), year2.getText())
                                }
                            }
                        }

                        InputBox
                        {

                            Text{
                                text: "Time format: 0:00:00"
                            }

                            id: starttime
                            name: "Start time"
                        }
                        InputBox
                        {
                            Text{
                                text: "Time format: 0:00:00"
                            }

                            id: endttime
                            name: "End time"
                        }
                    }
                    Row
                    {
                        spacing: 20

                        RacetagComboBox
                        {
                            id: racetag1
                            name: "Race tag 1"
                        }
                        RacetagComboBox
                        {
                            id: racetag2
                            name: "Race tag 2"
                        }
                        InputBox
                        {
                            id: athletename
                            name: "Athlete name"
                        }
                        InputBox
                        {
                            id: sizeofranking
                            name: "size of ranking:"
                        }
                    }
                    Row
                    {
                        spacing: 20

                        Column
                        {
                            id: gender
                            function getText()
                            {
                                return genderCombo.currentText;
                            }

                            Text
                            {
                                text: "Gender:"
                            }
                            ComboBox
                            {
                                id: genderCombo
                                currentIndex: 0
                                model: ListModel {
                                    id: genderItems
                                    ListElement { text: "M" }
                                    ListElement { text: "N" }
                                }
                            }
                        }
                    }

                }
            }

        }// Column
        Row
        {

            Button
            {
                text: "Search"
                onClicked: controller.search(root.state, year1.getText(), year2.getText(), starttime.getText(),
                                             endttime.getText(), racetag1.getText(), racetag2.getText(),
                                             athletename.getText(), sizeofranking.getText(), gender.getText())
            }
        }
    }//Column
}
