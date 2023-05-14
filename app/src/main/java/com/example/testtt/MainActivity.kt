package com.example.testtt

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle

const val WARNING_ZONE = 60
const val DANGER_ZONE = 30

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }
}
