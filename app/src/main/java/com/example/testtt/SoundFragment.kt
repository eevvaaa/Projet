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
import com.example.testtt.databinding.FragmentSoundBinding
import com.example.testtt.databinding.FragmentVisualBinding

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

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        binding.backButton.setOnClickListener {
            val action = SoundFragmentDirections.actionSoundFragmentToHomepageFragment()
            findNavController().navigate(action)
        }

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


        }
    }
}