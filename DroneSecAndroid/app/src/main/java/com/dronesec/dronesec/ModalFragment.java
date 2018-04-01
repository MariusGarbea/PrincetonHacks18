package com.dronesec.dronesec;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;

public class ModalFragment extends DialogFragment {
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setMessage("Suspicious movement has been detected!")
                .setPositiveButton("CHECK CELL", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        // Send new cell to Firebase
                    }
                })
                .setNegativeButton("IGNORE", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        // Close modal
                        dialog.dismiss();
                    }
                });
        return builder.create();
    }
}
