import React, { Component } from 'react';
import Data from './Data';
import Row from './Row';
import firebase from 'firebase';
import './App.css';

// let selectedCells = new Set();
let config = {
  'apiKey': "AIzaSyDmHxxMpjsEkT4AG3_th-nZ6gtt_ZhhqQ4",
  'authDomain': "whiteboard-21f79.firebaseapp.com",
  'databaseURL': "https://whiteboard-21f79.firebaseio.com",
  'projectId': "whiteboard-21f79",
  'storageBucket': "whiteboard-21f79.appspot.com",
  'messagingSenderId': "248376421307"
};

firebase.initializeApp(config);
const data = firebase.database().ref('droneSec/data');
const dataRobot = firebase.database().ref('droneSec/robot');

class App extends Component {

  state = {
    data: "0000000000000000",
    phoneNumbers: "",

  }

  componentDidMount() {
    data.once('value').then(elem => this.setState({ data: elem.val().value }));
    data.on('child_changed', elem => {
      this.setState({ data: elem.val() });
    });
  }

  // selectCell = (e) => {
  //   let id = e.target.id;
  //   if(selectedCells.has(id)) {
  //     selectedCells.delete(id);
  //     document.getElementById(id).style.backgroundColor = "#88cc00";
  //   } else if(selectedCells.size === 0) {
  //     selectedCells.add(id);
  //     document.getElementById(id).style.backgroundColor = "#ff4d4d";
  //     let val = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  //     val[id-1] = 1;
  //     data.update({ 'value': val.join("") })
  //   }
  // }

  handleChange = (e) => {
    this.setState({ phoneNumbers: e.target.value });
  }

  render() {
    return (
      <div className="container">
        <Data data={this.state.data} phoneNumbers={this.state.phoneNumbers} />
        <table className="grid">
          <tbody>
            <Row min={0} max={4} onClick={this.selectCell} />
            <Row min={4} max={8} onClick={this.selectCell} />
            <Row min={8} max={12} onClick={this.selectCell} />
            <Row min={12} max={16} onClick={this.selectCell} />
          </tbody>
        </table>
        <div className="panel">
          <p className="title">Notification Numbers</p>
          <textarea className="box" value={this.state.phoneNumbers} onChange={this.handleChange} />
        </div>
      </div>
    );
  }
}

export { App, data, dataRobot };
