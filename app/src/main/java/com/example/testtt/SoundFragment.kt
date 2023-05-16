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
    
    //Media player pour faire les sons
    private lateinit var warning: MediaPlayer
    private lateinit var danger: MediaPlayer

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        binding = FragmentSoundBinding.inflate(inflater, container, false)
        return binding.root
    }



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
            handler.postDelayed(this, delay)
        }
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
        warning.isLooping=false
        danger = MediaPlayer.create(requireContext(), R.raw.danger)
        danger.isLooping=false


        //runnable quand le valeur du capteur changer
        val runnableSon = object : Runnable{
            val capteur = arrayOf(intArrayOf(90,90,90,90,90,45,34,24,11,4,38,49,68,90,90,90,90,90,90,90,90,90,90,90,90), intArrayOf(91,90,59,45,36,29,12,35,40,69,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90), intArrayOf(92,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90),intArrayOf(93,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90),intArrayOf(94,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,45,36,20,10,17,34,69),intArrayOf(95,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,35,34,27,12,19,49,68,90,90),intArrayOf(96,90,90,90,90,90,90,90,90,90,90,90,90,90,50,34,29,12,12,36,90,90,90,90,90,),intArrayOf(97,90,90,90,90,90,90,90,46,12,25,34,56,94,90,90,90,90,90,90,90,90,90,90,90))
            var i =0
            override fun run() {
               var i=0
            var j=0
            var k=0
            var l=0
            var m=0
            var n=0
            var p=0
            var q=0
            override fun run() {
                retourSon(capteur[0][i],capteur[1][j],capteur[2][k],capteur[3][l],capteur[4][m],capteur[5][n],capteur[6][p],capteur[7][q])
                i++;j++;k++;l++;m++;n++;p++;q++
                if (i == capteur[0].size) {
                    i = 0
                }
                if (j == capteur[1].size) {
                    j = 0
                }
                if (k == capteur[2].size) {
                    k = 0
                }
                if (l == capteur[3].size) {
                    l = 0
                }
                if (m == capteur[4].size) {
                    m = 0
                }
                if (n == capteur[5].size) {
                    n= 0
                }
                if (p == capteur[6].size) {
                    p= 0
                }
                if (q == capteur[7].size) {
                    q = 0
                }
                handler.postDelayed(this, delay)
            }
        }

        handler.post(runnableSon)

        // Définir le listener pour les éléments de la Bottom Navigation View
        binding.bottomNavigation.setOnNavigationItemSelectedListener { menuItem ->
            when (menuItem.itemId) {
                R.id.perso -> {
                    handler.removeCallbacks(dangerRunnable)
                    handler.removeCallbacks(warningRunnable)
                    handler.removeCallbacks(runnableSon)
                    danger.isLooping = false
                    warning.isLooping =false
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
                    handler.removeCallbacks(dangerRunnable)
                    handler.removeCallbacks(warningRunnable)
                    handler.removeCallbacks(runnableSon)
                    danger.isLooping = false
                    warning.isLooping =false
                    findNavController().navigate(R.id.visualFragment)
                    true
                }
                R.id.urgences -> {
                    handler.removeCallbacks(dangerRunnable)
                    handler.removeCallbacks(warningRunnable)
                    handler.removeCallbacks(runnableSon)
                    danger.isLooping = false
                    warning.isLooping =false
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
                    handler.removeCallbacks(dangerRunnable)
                    handler.removeCallbacks(warningRunnable)
                    handler.removeCallbacks(runnableSon)
                    danger.isLooping = false
                    warning.isLooping =false
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
    
       //truc obligatoire pour pas surcharger
    override fun onDestroy() {
        warning.release()
        danger.release()
        super.onDestroy()
    }
}
