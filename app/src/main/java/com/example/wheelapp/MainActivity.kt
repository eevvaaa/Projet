package com.example.wheelapp

import android.annotation.SuppressLint
import android.app.Activity.RESULT_OK
import android.app.AlertDialog
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.content.*
import android.content.pm.PackageManager
import android.os.Build
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.*
import androidx.activity.result.contract.ActivityResultContracts
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat



class MainActivity : AppCompatActivity() {

    private val REQUEST_ENABLE_BT = 1 // Request code for enabling Bluetooth
    private val DEVICE_ADDRESS = "78:21:84:A6:8E:42"//"08:B6:1F:C1:B1:02" // M5Stack's Bluetooth address
    private val SERVICE_UUID =
        UUID.fromString("00001101-0000-1000-8000-00805F9B34FB") // Replace with your desired UUID


    private lateinit var bluetoothAdapter: BluetoothAdapter
    private lateinit var m5StackDevice: BluetoothDevice
    private var connectThread: ConnectThread? = null
    private var connectedThread: ConnectedThread? = null

    @SuppressLint("MissingPermission")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Initialize Bluetooth adapter
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()

        // Check if Bluetooth is enabled, and request to enable it if not
        if (!bluetoothAdapter.isEnabled) {
            val enableBtIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT)
            log("bluettoth enabled")

        }

        log("bluetooth already enabled")

        // Get the M5Stack device by its address
        m5StackDevice = bluetoothAdapter.getRemoteDevice(DEVICE_ADDRESS)

        // Start the connection process
        connectToM5Stack()
    }

    private fun connectToM5Stack() {
        connectThread = ConnectThread(m5StackDevice)
        connectThread?.start()
    }

    // Thread for establishing the Bluetooth connection
    @SuppressLint("MissingPermission")
    private inner class ConnectThread(device: BluetoothDevice) : Thread() {
        private val socket: BluetoothSocket? by lazy(LazyThreadSafetyMode.NONE) {
            device.createRfcommSocketToServiceRecord(SERVICE_UUID)
        }

        @SuppressLint("MissingPermission")
        override fun run() {
            // Cancel discovery as it slows down the connection
            bluetoothAdapter.cancelDiscovery()
            log("discovery disabled")

            try {
                // Connect to the M5Stack device
                socket?.connect()
                log("socket connected")
            } catch (connectException: IOException) {
                // Unable to connect; close the socket and return
                try {
                    socket?.close()
                    log("Unable to connect, socket closed")
                } catch (closeException: IOException) {
                    closeException.printStackTrace()
                }
                return
            }

            // Start the connected thread for communication
            connectedThread = ConnectedThread(socket!!)
            connectedThread?.start()
            log("thred connected")
        }

        fun cancel() {
            try {
                socket?.close()
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
    }

    // Thread for handling the Bluetooth communication
    private inner class ConnectedThread(private val socket: BluetoothSocket) : Thread() {
        private val inputStream: InputStream = socket.inputStream

        override fun run() {
            val buffer = ByteArray(1024)
            var bytesRead: Int

            // Keep listening to the InputStream until an exception occurs
            while (true) {
                try {
                    // Read from the InputStream
                    bytesRead = inputStream.read(buffer)
                    // Handle the received data
                    val receivedData = buffer.copyOf(bytesRead)
                    // Process the received data as needed
                    log(receivedData.toString())
                } catch (e: IOException) {
                    e.printStackTrace()
                    break
                }
            }
        }
    }


    fun log(message:String){
        Log.d("hello", message)
    }


}

