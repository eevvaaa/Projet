package com.example.testtt

import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper

// La base de données en local qui va stocker les info perso de l'utilisateur

class BDInfoPerso(context: Context) : SQLiteOpenHelper(context, "BDInfoPerso", null, 1) {

    override fun onCreate(db: SQLiteDatabase) {
        db.execSQL("CREATE TABLE MonTableau (nom TEXT)")
    }

    override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
        db.execSQL("DROP TABLE IF EXISTS MonTableau")
        onCreate(db)
    }

}
