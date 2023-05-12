package com.example.testtt

import android.app.AlertDialog
import android.graphics.Color
import android.graphics.PorterDuff
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.RadioButton
import android.widget.Switch
import androidx.navigation.fragment.findNavController
import com.example.testtt.databinding.FragmentVisualBinding


class VisualFragment : Fragment() {

    private lateinit var binding: FragmentVisualBinding

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        binding = FragmentVisualBinding.inflate(inflater, container, false)

            val navController = findNavController()

            return binding.root
        }

    //fonctions pour afficher distance
    fun retourDef(valeur: Int){
        if(valeur<30){
            binding.capteur1.setColorFilter(resources.getColor(R.color.red), PorterDuff.Mode.MULTIPLY)
        }
        if(valeur in 30.. 59){
            binding.capteur1.setColorFilter( resources.getColor(R.color.yellow),PorterDuff.Mode.MULTIPLY)}
        if(valeur >= 60){
            binding.capteur1.setColorFilter(resources.getColor(R.color.green), PorterDuff.Mode.MULTIPLY)
        }
    }

    fun retourDeut(valeur: Int){
        if(valeur<30){
            binding.capteur1.setColorFilter(resources.getColor(R.color.deut_close), PorterDuff.Mode.MULTIPLY)
        }
        if(valeur in 30.. 59){
            binding.capteur1.setColorFilter( resources.getColor(R.color.deut_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur >= 60){
            binding.capteur1.setColorFilter(resources.getColor(R.color.deut_far), PorterDuff.Mode.MULTIPLY)
        }
    }

    fun retourTri(valeur: Int){
        if(valeur<30){
            binding.capteur1.setColorFilter(resources.getColor(R.color.tri_close), PorterDuff.Mode.MULTIPLY)
        }
        if(valeur in 30.. 59){
            binding.capteur1.setColorFilter( resources.getColor(R.color.tri_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur >= 60){
            binding.capteur1.setColorFilter(resources.getColor(R.color.tri_far), PorterDuff.Mode.MULTIPLY)
        }
    }

    fun retourPro(valeur: Int){
        if(valeur<30){
            binding.capteur1.setColorFilter(resources.getColor(R.color.prota_close), PorterDuff.Mode.MULTIPLY)
        }
        if(valeur in 30.. 59){
            binding.capteur1.setColorFilter(resources.getColor(R.color.prota_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur >= 60){
            binding.capteur1.setColorFilter(resources.getColor(R.color.prota_far), PorterDuff.Mode.MULTIPLY)
        }
    }





    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        binding.backButton.setOnClickListener{
            val action = VisualFragmentDirections.actionVisualFragmentToHomepageFragment()
            findNavController().navigate(action)
        }



        // pour afficher la distance quand la valeur change
        val delay = 2000L // 2 secondes
        val handler = Handler(Looper.getMainLooper())


        //par defaut
        val runnable = object : Runnable {
            val capteur = arrayOf<Int>(1,32,93,4,45,68)
            var i=0
            override fun run() {
                retourDef(capteur[i])
                i++
                if (i == capteur.size) {
                    i = 0
                }
                // post the runnable again after 2 seconds
                handler.postDelayed(this, delay)
            }

        }
        // start the runnable
        handler.postDelayed(runnable, delay)

        //quand boutton defaut
        val runnable1 = object : Runnable {
            val capteur = arrayOf<Int>(1,32,93,4,45,68)
            var i=0
            override fun run() {
                retourDef(capteur[i])
                i++
                if (i == capteur.size) {
                    i = 0
                }
                // post the runnable again after 2 seconds
                handler.postDelayed(this, delay)
            }
        }

        //quand boutton deut
        val runnable2 = object : Runnable {
            val capteur = arrayOf<Int>(1,32,93,4,45,68)
            var i=0
            override fun run() {
                retourDeut(capteur[i])
                i++
                if (i == capteur.size) {
                    i = 0
                }
                // post the runnable again after 2 seconds
                handler.postDelayed(this, delay)
            }
        }

        //qaund boutton pro
        val runnable3 = object : Runnable {
            val capteur = arrayOf<Int>(1,32,93,4,45,68)
            var i=0
            override fun run() {
                retourPro(capteur[i])
                i++
                if (i == capteur.size) {
                    i = 0
                }
                // post the runnable again after 2 seconds
                handler.postDelayed(this, delay)
            }
        }


        //quand boutton tri
        val runnable4 = object : Runnable {
            val capteur = arrayOf<Int>(1,32,93,4,45,68)
            var i=0
            override fun run() {
                retourTri(capteur[i])
                i++
                if (i == capteur.size) {
                    i = 0
                }
                // post the runnable again after 2 seconds
                handler.postDelayed(this, delay)
            }
        }





        binding.setting.setOnClickListener {
            // Créer une AlertDialog pour afficher le bouton on/off
            val dialogBuilder = AlertDialog.Builder(requireContext())
            dialogBuilder.setTitle("Options")
            val switchView = layoutInflater.inflate(R.layout.fragment_visual_option, null)
            dialogBuilder.setView(switchView)
            val toggleSwitch = switchView.findViewById<Switch>(R.id.toggleSwitchSo)
            val RBdefaut = switchView.findViewById<RadioButton>(R.id.radioButtonD)
            val RBprotanopia = switchView.findViewById<RadioButton>(R.id.radioButtonPro)
            val RBdeuteranopia = switchView.findViewById<RadioButton>(R.id.radioButtonDeut)
            val RBtritanopia = switchView.findViewById<RadioButton>(R.id.radioButtonTri)

            // Ajouter un bouton OK pour fermer la fenêtre
            dialogBuilder.setPositiveButton("OK") { _, _ ->
                // Naviguer vers le fragment approprié en fonction de l'état du bouton on/off
                if (toggleSwitch.isChecked) {

                    findNavController().navigate(R.id.soundAndVisualFragment)
                } else {
                    findNavController().navigate(R.id.visualFragment)
                }
            }

            dialogBuilder.setPositiveButton("OK") { _, _ ->

                //coche des palettes

                if (RBdefaut.isChecked) {
                    binding.far.background.setTint(resources.getColor(R.color.green))
                    binding.middle.background.setTint(resources.getColor(R.color.yellow))
                    binding.close.background.setTint(resources.getColor(R.color.red))
                    Log.d("hello", "aaaaaaaaaaaaaaaa")


                    // start the runnable
                    handler.postDelayed(runnable1, delay)


                    //stop les autres runnable
                    handler.removeCallbacks(runnable)
                    handler.removeCallbacks(runnable2)
                    handler.removeCallbacks(runnable3)
                    handler.removeCallbacks(runnable4)

                }


                if (RBdeuteranopia.isChecked) {
                    binding.far.background.setTint(resources.getColor(R.color.deut_far))
                    binding.middle.background.setTint(resources.getColor(R.color.deut_next))
                    binding.close.background.setTint(resources.getColor(R.color.deut_close))
                    Log.d("hello", "bbbbbbbbbbbbbbb")



                    // start the runnable
                    handler.postDelayed(runnable2, delay)

                    //stop le runnable par defaut
                    handler.removeCallbacks(runnable)
                    handler.removeCallbacks(runnable1)
                    handler.removeCallbacks(runnable3)
                    handler.removeCallbacks(runnable4)

                }


                if (RBprotanopia.isChecked) {
                    binding.far.background.setTint(resources.getColor(R.color.prota_far))
                    binding.middle.background.setTint(resources.getColor(R.color.prota_next))
                    binding.close.background.setTint(resources.getColor(R.color.prota_close))
                    Log.d("hello", "ccccccccccccc")


                    // start the runnable
                    handler.postDelayed(runnable3, delay)

                    //stop le runnable par defaut
                    handler.removeCallbacks(runnable)
                    handler.removeCallbacks(runnable1)
                    handler.removeCallbacks(runnable2)
                    handler.removeCallbacks(runnable4)
                }


                if (RBtritanopia.isChecked) {
                    binding.far.background.setTint(resources.getColor(R.color.tri_far))
                    binding.middle.background.setTint(resources.getColor(R.color.tri_next))
                    binding.close.background.setTint(resources.getColor(R.color.tri_close
                    ))
                    Log.d("hello", "ddddddddddddddddd")


                    // start the runnable
                    handler.postDelayed(runnable4, delay)

                    //stop les autres runnable
                    handler.removeCallbacks(runnable)
                    handler.removeCallbacks(runnable1)
                    handler.removeCallbacks(runnable2)
                    handler.removeCallbacks(runnable3)
                }
            }

            // Créer et afficher la fenêtre
            val dialog = dialogBuilder.create()
            dialog.show()
        }




        // Définir le listener pour les éléments de la Bottom Navigation View
        binding.bottomNavigation.setOnNavigationItemSelectedListener { menuItem ->
            when (menuItem.itemId) {
                R.id.perso -> {
                    findNavController().navigate(R.id.persoFragment)
                    true
                }
                R.id.sound -> {
                    findNavController().navigate(R.id.soundFragment)
                    true
                }
                R.id.eyes -> {
                    binding.messageAlreadyThere.visibility = View.VISIBLE
                    Handler(Looper.getMainLooper()).postDelayed({
                        binding.messageAlreadyThere.visibility = View.INVISIBLE
                    }, 3000)
                    true
                }
                R.id.urgences -> {
                    findNavController().navigate(R.id.urgencesFragment)
                    true
                }
                else -> false
            }
        }






    }
}
