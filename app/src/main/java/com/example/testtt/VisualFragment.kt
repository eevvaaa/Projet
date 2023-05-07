package com.example.testtt

import android.app.AlertDialog
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Switch
import androidx.navigation.fragment.findNavController
import androidx.navigation.ui.AppBarConfiguration
import androidx.navigation.ui.setupWithNavController
import com.example.testtt.databinding.FragmentVisualBinding

class VisualFragment : Fragment() {

    private lateinit var binding: FragmentVisualBinding

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        binding = FragmentVisualBinding.inflate(inflater, container, false)

            val navController = findNavController()

            return binding.root
        }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        binding.backButton.setOnClickListener{
            val action = VisualFragmentDirections.actionVisualFragmentToHomepageFragment()
            findNavController().navigate(action)
        }

        binding.setting.setOnClickListener {
            // Créer une AlertDialog pour afficher le bouton on/off
            val dialogBuilder = AlertDialog.Builder(requireContext())
            dialogBuilder.setTitle("Sound Option")
            val switchView = layoutInflater.inflate(R.layout.fragment_sound_option, null)
            dialogBuilder.setView(switchView)
            val toggleSwitch = switchView.findViewById<Switch>(R.id.toggleSwitch)

            // Ajouter un bouton OK pour fermer la fenêtre
            dialogBuilder.setPositiveButton("OK") { _, _ ->
                // Naviguer vers le fragment approprié en fonction de l'état du bouton on/off
                if (toggleSwitch.isChecked) {
                    findNavController().navigate(R.id.visualFragment)
                } else {
                    findNavController().navigate(R.id.homepageFragment)
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
                        binding.messageAlreadyThere.visibility = View.GONE
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
