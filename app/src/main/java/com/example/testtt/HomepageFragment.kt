package com.example.testtt

import android.annotation.SuppressLint
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.core.content.ContextCompat
import androidx.navigation.fragment.findNavController
import com.example.testtt.databinding.FragmentHomepageBinding

class HomepageFragment : Fragment() {

    private lateinit var binding: FragmentHomepageBinding

    // array of image IDs
    private val images = arrayOf(R.drawable.logo_app, R.drawable.logo_app1, R.drawable.logo_app, R.drawable.image1, R.drawable.image2, R.drawable.image3, R.drawable.image4)

    // global variables to store button state and ID of last clicked button
    private var isSoundButtonSelected = false
    private var lastCheckedButtonId = -1

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        binding = FragmentHomepageBinding.inflate(inflater, container, false)
        return binding.root
    }

    @SuppressLint("ResourceAsColor")
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        // initialize isSoundButtonSelected as true
        var isSoundButtonSelected = true

        // create a Handler to change image every 2 seconds
        val handler = Handler(Looper.getMainLooper())
        val delay = 2000L // 2 secondes

        // create a Runnable to switch images
        val runnable = object : Runnable {
            var index = 0
            override fun run() {
                // set the image to the current index
                binding.imageHomepage.setImageResource(images[index])
                index++
                if (index == images.size) {
                    index = 0
                }
                // post the runnable again after 2 seconds
                handler.postDelayed(this, delay)
            }
        }
        // start the runnable
        handler.postDelayed(runnable, delay)

        // add a listener to the ToggleGroup to change button colors when the button is clicked
        binding.toggleGroup.addOnButtonCheckedListener { group, checkedId, isChecked ->
            if (isChecked) {
                // if the sound/visual button is clicked, switch his color and buttonGo's color to green
                if (checkedId != lastCheckedButtonId) {
                    if (checkedId == binding.soundButton.id) {
                        binding.soundButton.setBackgroundColor(ContextCompat.getColor(requireContext(), R.color.green))
                        binding.visualButton.setBackgroundColor(ContextCompat.getColor(requireContext(), R.color.white))
                        binding.buttonGo.setBackgroundColor(ContextCompat.getColor(requireContext(), R.color.green))
                        isSoundButtonSelected = true
                    } else {
                        binding.visualButton.setBackgroundColor(ContextCompat.getColor(requireContext(), R.color.green))
                        binding.soundButton.setBackgroundColor(ContextCompat.getColor(requireContext(), R.color.white))
                        binding.buttonGo.setBackgroundColor(ContextCompat.getColor(requireContext(), R.color.green))
                        isSoundButtonSelected = false
                    }
                } else {
                    // if we reclick on the same button, we reinitialise the colors to white
                    binding.soundButton.setBackgroundColor(ContextCompat.getColor(requireContext(), R.color.white))
                    binding.visualButton.setBackgroundColor(ContextCompat.getColor(requireContext(), R.color.white))
                    binding.buttonGo.setBackgroundColor(ContextCompat.getColor(requireContext(), R.color.white))
                    isSoundButtonSelected = false
                }
                lastCheckedButtonId = checkedId
            }
        }

        binding.buttonGo.setOnClickListener{
            if (isSoundButtonSelected) {
                // if soundButton has been selected, we open the soundFragment
                val action = HomepageFragmentDirections.actionHomepageFragmentToSoundFragment()
                findNavController().navigate(action)
            } else {
                // else, we open the visualFragment
                val action = HomepageFragmentDirections.actionHomepageFragmentToVisualFragment()
                findNavController().navigate(action)
            }
        }
    }
}
