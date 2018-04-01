package com.dronesec.dronesec;

import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.HashSet;
import java.util.Set;

public class GridActivity extends AppCompatActivity implements View.OnClickListener {

    private Set<Integer> selectedCells= new HashSet<>();
    private static final int DEFAULT_BKGCOLOR = 0xEEEEEE;
    private static final int CELL_COLOR = Color.parseColor("#88cc00");
    private TextView textBox;
    private FirebaseDatabase database = FirebaseDatabase.getInstance();
    private DatabaseReference myRef = database.getReference("droneSec/data");
    private String cellsStatus;
    private int selectedCell;
    private ModalFragment modalFragment = new ModalFragment();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textBox = findViewById(R.id.textView);
        textBox.setMovementMethod(new ScrollingMovementMethod());

        Button b1 = findViewById(R.id.button1);
        Button b2 = findViewById(R.id.button2);
        Button b3 = findViewById(R.id.button3);
        Button b4 = findViewById(R.id.button4);
        Button b5 = findViewById(R.id.button5);
        Button b6 = findViewById(R.id.button6);
        Button b7 = findViewById(R.id.button7);
        Button b8 = findViewById(R.id.button8);
        Button b9 = findViewById(R.id.button9);
        Button b10 = findViewById(R.id.button10);
        Button b11 = findViewById(R.id.button11);
        Button b12 = findViewById(R.id.button12);
        Button b13 = findViewById(R.id.button13);
        Button b14 = findViewById(R.id.button14);
        Button b15 = findViewById(R.id.button15);
        Button b16 = findViewById(R.id.button16);
        b1.setOnClickListener(this);
        b2.setOnClickListener(this);
        b3.setOnClickListener(this);
        b4.setOnClickListener(this);
        b5.setOnClickListener(this);
        b6.setOnClickListener(this);
        b7.setOnClickListener(this);
        b8.setOnClickListener(this);
        b9.setOnClickListener(this);
        b10.setOnClickListener(this);
        b11.setOnClickListener(this);
        b12.setOnClickListener(this);
        b13.setOnClickListener(this);
        b14.setOnClickListener(this);
        b15.setOnClickListener(this);
        b16.setOnClickListener(this);

        myRef.addChildEventListener(new ChildEventListener() {
            @Override
            public void onChildAdded(DataSnapshot dataSnapshot, String s) {

            }

            @Override
            public void onChildChanged(DataSnapshot dataSnapshot, String s) {
                for(DataSnapshot snapshot : dataSnapshot.getChildren()) {
                    String value = (String)snapshot.child("value").getValue();
                    Toast.makeText(GridActivity.this, value, Toast.LENGTH_SHORT).show();
                    if (value != null) {
                        cellsStatus = value;
                        textBox.append("Movement detected on " + cellsStatus);
                        for(int i = 0; i < cellsStatus.length(); i++) {
                            char c = cellsStatus.charAt(i);
                            if(c == '1') {
                                selectedCell = i+1;
                                modalFragment.show(getFragmentManager(), "action");
                                return;
                            }
                        }
                    } else {
                        cellsStatus = "No data";
                        return;
                    }
                }
            }

            @Override
            public void onChildRemoved(DataSnapshot dataSnapshot) {

            }

            @Override
            public void onChildMoved(DataSnapshot dataSnapshot, String s) {

            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });
    }

    public void onClick(View view) {
        Integer buttonID = view.getId();
        Button b = (Button) view;
        selectCell(buttonID);
        textBox.append("Movement detected on " + b.getText().toString() + "\n");
    }

    private void selectCell(Integer id) {
        if(selectedCells.contains(id)) {
            selectedCells.remove(id);
            findViewById(id).setBackgroundColor(DEFAULT_BKGCOLOR);
        } else {
            selectedCells.add(id);
            findViewById(id).setBackgroundColor(CELL_COLOR);
        }
    }

    public void setValueInDatabase(String value) {
        myRef.setValue(value);
    }



    @Override
    public void onPointerCaptureChanged(boolean hasCapture) {

    }
}
