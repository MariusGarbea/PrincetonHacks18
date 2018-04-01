import React from 'react';
import './App.css';

let Row = ({ min, max, onClick }) => {

  let ids = [];
  for(let i = min+1; i<=max; i++) {
    ids.push(i);
  }

  return(
    <tr>
      {
        ids.map(id => {
          return <td id={id} key={id} onClick={onClick}>Cell {id}</td>
        })
      }
    </tr>
  );
}

export default Row;
