package com.example.testtt

import android.annotation.SuppressLint
import android.app.AlertDialog
import android.app.WallpaperColors
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Switch
import android.media.MediaPlayer
import android.util.Log
import androidx.core.content.ContentProviderCompat.requireContext
import androidx.navigation.fragment.findNavController
import com.example.testtt.databinding.FragmentSoundBinding

class SoundFragment : Fragment() {

    private lateinit var binding: FragmentSoundBinding

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        binding = FragmentSoundBinding.inflate(inflater, container, false)
        return binding.root
    }



    //Media player pour faire les sons
    private lateinit var warning: MediaPlayer
    private lateinit var danger: MediaPlayer

    val delay = 2000L // 2 secondes
    val handler = Handler(Looper.getMainLooper())

    //runnable pour boucler le son warning
    var warningRunnable = object : Runnable{
        override fun run() {
            warning.seekTo(0)
            warning.start()
            handler.postDelayed(this, delay)
        }
    }

    //runnable pour boucler le son danger
    var dangerRunnable = object : Runnable{
        override fun run() {
            danger.seekTo(0)
            danger.start()
            handler.postDelayed(this, 0)
        }
    }


    //fct pour changer de son en fct de la valeur
    //ça marche pas pour le moment
    fun retourSon(valeur: Int){
        if(valeur< DANGER_ZONE){
            handler.removeCallbacks(warningRunnable)
            handler.postDelayed(dangerRunnable,delay)}
        if(valeur in DANGER_ZONE..WARNING_ZONE){
            handler.removeCallbacks(dangerRunnable)
            handler.postDelayed(warningRunnable,delay) }
        if(valeur > WARNING_ZONE){
            handler.removeCallbacks(warningRunnable)
            handler.removeCallbacks(dangerRunnable)
        }
    }

    //truc obligatoire pour pas surcharger
    override fun onDestroy() {
        warning.release()
        danger.release()
        super.onDestroy()
    }


    @SuppressLint("MissingInflatedId")
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        binding.backButton.setOnClickListener {
            val action = SoundFragmentDirections.actionSoundFragmentToHomepageFragment()
            findNavController().navigate(action)
        }

        //création des mediaplayer
        warning = MediaPlayer.create(requireContext(), R.raw.warning)
        warning.isLooping=true
        danger = MediaPlayer.create(requireContext(), R.raw.danger)
        danger.isLooping=true


        //runnable quand le valeur du capteur changer
        val runnable = object : Runnable{
            val capteur = arrayOf(1,2,6,4,68,62,62,62,50,50,50,50,12,12,12,12)
            var i =0
            override fun run() {
                retourSon(capteur[i])
                i++
                if(i == capteur.size) {
                    i = 0
                }
                handler.postDelayed(this, delay)
                Log.d("hello","tour : " + i + "\nvaleur : " + capteur[i])
            }
        }

       handler.postDelayed(runnable,delay)





        // Définir le listener pour les éléments de la Bottom Navigation View
        binding.bottomNavigation.setOnNavigationItemSelectedListener { menuItem ->
            when (menuItem.itemId) {
                R.id.perso -> {
                    findNavController().navigate(R.id.persoFragment)
                    true
                }
                R.id.sound -> {
                    binding.messageAlreadyThere.visibility = View.VISIBLE
                    Handler(Looper.getMainLooper()).postDelayed({
                        binding.messageAlreadyThere.visibility = View.GONE
                    }, 3000)
                    true
                }
                R.id.eyes -> {
                    findNavController().navigate(R.id.visualFragment)
                    true
                }
                R.id.urgences -> {
                    findNavController().navigate(R.id.urgencesFragment)
                    true
                }
                else -> false
            }
        }

        binding.settingVisual.setOnClickListener {
            // Créer une AlertDialog pour afficher le bouton on/off
            val dialogBuilder = AlertDialog.Builder(requireContext())
            dialogBuilder.setTitle(getString(R.string.opt))
            val switchView = layoutInflater.inflate(R.layout.fragment_sound_option, null)
            dialogBuilder.setView(switchView)
            val toggleSwitch = switchView.findViewById<Switch>(R.id.toggleSwitchVis)

            // Ajouter un bouton OK pour fermer la fenêtre
            dialogBuilder.setPositiveButton("OK") { _, _ ->
                // Naviguer vers le fragment approprié en fonction de l'état du bouton on/off
                if (toggleSwitch.isChecked) {
                    findNavController().navigate(R.id.soundAndVisualFragment)
                } else {
                    findNavController().navigate(R.id.soundFragment)
                }
            }

            // Créer et afficher la fenêtre
            val dialog = dialogBuilder.create()
            dialog.show()
        }
    }
}
