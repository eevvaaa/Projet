package com.example.wheelapp

import android.R
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.content.DialogInterface
import android.content.IntentFilter
import android.content.pm.PackageManager
import android.os.Build
import android.os.Bundle
import android.view.View
import android.widget.*
import android.widget.Button
import android.widget.ListView
import android.widget.TextView
import android.widget.ToggleButton
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat


class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val statusText : TextView = findViewById(R.id.StatusText)
        enableBluetooth = findViewById<View>(R.id.enableBluetoothButton) as Button
        connectSystem = findViewById<View>(R.id.connect) as Button
        lvDiscovered = findViewById<View>(R.id.discoveredDevice) as ListView
        lvPaired = findViewById<View>(R.id.pairedDevices) as ListView
        scanBluetooth = findViewById<View>(R.id.toggleScan) as ToggleButton

        btPairedDevice = ArrayAdapter<Any>(this, R.layout.simple_list_item_1)
        lvPaired.setAdapter(btPairedDevice)
        btArrayAdapter = ArrayAdapter<Any>(this, R.layout.simple_list_item_1)
        lvDiscovered.setAdapter(btArrayAdapter)

        enableBluetooth.setOnClickListener(btnEnableBluetoothOnClickListener)
        scanBluetooth.setOnCheckedChangeListener(btnScanDeviceOnCheckedListener)
        connectSystem.setOnClickListener(btnConnectOnClickListener)

        connectSystem.setEnabled(false)
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {  // Only ask for these permissions on runtime when running Android 6.0 or higher
            when (ContextCompat.checkSelfPermission(
                baseContext,
                Manifest.permission.ACCESS_COARSE_LOCATION
            )) {
                PackageManager.PERMISSION_DENIED -> Builder(this)
                    .setTitle("Runtime Permissions up ahead")
                    .setMessage("Permission is needed to scan for bluetooth devices")
                    .setPositiveButton("Okay", DialogInterface.OnClickListener { dialog, which ->
                        if (ContextCompat.checkSelfPermission(
                                baseContext,
                                Manifest.permission.ACCESS_COARSE_LOCATION
                            ) != PackageManager.PERMISSION_GRANTED
                        ) {
                            ActivityCompat.requestPermissions(
                                this@MainActivity,
                                arrayOf(Manifest.permission.ACCESS_COARSE_LOCATION),
                                1
                            )
                        }
                    })
                    .setIcon(R.drawable.ic_dialog_alert)
                    .show()
                PackageManager.PERMISSION_GRANTED -> {}
            }
        }

        CheckAndEnableBlueToothState()

        val filter = IntentFilter()
        filter.addAction(BluetoothDevice.ACTION_FOUND)
        filter.addAction(BluetoothAdapter.ACTION_STATE_CHANGED)
        filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED)
        filter.addAction(BluetoothDevice.ACTION_ACL_CONNECTED)
        filter.addAction(BluetoothDevice.ACTION_ACL_DISCONNECTED)
        registerReceiver(ActionFoundReceiver, filter)


    }
}
