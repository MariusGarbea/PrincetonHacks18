import React, { Component } from 'react';
import Modal from 'react-modal';
import { data, dataRobot } from './App';
import './App.css';

const customStyles = {
  content : {
    top                   : '50%',
    left                  : '50%',
    right                 : 'auto',
    bottom                : 'auto',
    marginRight           : '-50%',
    transform             : 'translate(-50%, -50%)',
    backgroundColor       : '#d1d1e0'
  }
};

class Data extends Component {

  state = {
    modalIsOpen: false,
    selectedCell: ""
  }

  componentDidMount() {
    this.update(this.props)
  }

  componentWillReceiveProps(nextProps) {
    this.update(nextProps)
  }

  sendNotifications = (notification) => {
    let { phoneNumbers } = this.props;
    let numbers = phoneNumbers.split('\n');
    const req = (number) => fetch(`https://mmaris.lib.id/flyingsaucer@dev/?recipient=${number}&body=${notification}`)
                .then(response => response.json())
                .then(data => console.log(data));
    Promise
      .all(numbers.map(req))
      .then(() => console.log("Finished"));
  }

  closeModal = () => {
    this.setState({ modalIsOpen: false });
  }

  takeAction = (notification) => {
    this.sendNotifications(notification);
    dataRobot.update({ 'coor': this.state.selectedCell.toString() });
    this.ignore();
  }

  ignore = () => {
    this.closeModal();
    data.update({ 'value': '0000000000000000' });
    document.getElementById(this.state.selectedCell).style.backgroundColor = "#88cc00";
  }

  update = (nextProps) => {
    if(nextProps.data) {
      for(let i = 0; i<16; i++) {
        if(nextProps.data[i] === "1") {
          console.log(nextProps.data)
          this.setState({
            selectedCell: i+1,
            modalIsOpen: true
          });
          for(let i = 0; i<16; i++) {
            document.getElementById(i+1).style.backgroundColor = "#88cc00";
          }
          document.getElementById(i+1).style.backgroundColor = "#ff4d4d";
        }
      }
    }
  }

  render() {
    let { data } = this.props;
    let information = "";
    let clean = true;
    if(!data) {
      information = "No Data";
    } else {
      for(let state = 0; state<16; state++) {
        if(data[state] === "1") {
          clean = false;
          information = "Movement has been detected on cell " + this.state.selectedCell;
          continue;
        }
      }
      if(clean) {
        information = "Everything is good :)";
      }
    }
    return(
      <div className="panel">
        <Modal
          isOpen={this.state.modalIsOpen}
          style={customStyles}
          contentLabel="Intruder Detected!"
          overlayClassName="overlay"
        >
            <h1>Movement has been detected on cell {this.state.selectedCell}</h1>
            <h2>What action would you like to take?</h2>
            <button onClick={() => this.takeAction(information)}>Check Area</button>
            <button onClick={this.ignore}>Ignore</button>
        </Modal>
        <p className="title">Data</p>
        <div className="box">
          <div>
            { information }
          </div>
        </div>
      </div>
    );
  }
}

export default Data;
