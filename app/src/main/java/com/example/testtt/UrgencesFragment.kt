package com.example.testtt

import android.animation.ValueAnimator
import android.annotation.SuppressLint
import android.content.Intent
import android.graphics.Color
import android.net.Uri
import android.os.Bundle
import android.os.CountDownTimer
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.FrameLayout
import android.widget.TextView
import androidx.core.content.ContextCompat
import androidx.navigation.fragment.findNavController
import com.example.testtt.databinding.FragmentUrgencesBinding
import com.google.android.material.button.MaterialButton


class UrgencesFragment : Fragment() {

    private lateinit var binding: FragmentUrgencesBinding

    private var countDownTimer: CountDownTimer? = null

    private lateinit var countdownTextView: TextView
    private lateinit var letsGoButton: MaterialButton
    private lateinit var rootView: FrameLayout
    private var countdownTimer: CountDownTimer? = null
    private val phoneNumber = "0782000111" // numéro de téléphone à appeler

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        binding = FragmentUrgencesBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        binding.buttonStop.setOnClickListener {
            onButtonClicked()
        }

        binding.backButton.setOnClickListener {
            val action = UrgencesFragmentDirections.actionUrgencesFragmentToVisualFragment()
            findNavController().navigate(action)
        }
    }

    private fun startCountdown() {
        binding.buttonStop.isEnabled = true

        binding.buttonStop.setOnClickListener {
            onButtonClicked()
        }

        countdownTimer = object : CountDownTimer(5000, 1000) {


            override fun onTick(millisUntilFinished: Long) {
                val secondsLeft = millisUntilFinished / 1000
                binding.countdownTextview.text = secondsLeft.toString()
                val alpha = ((5000 - millisUntilFinished) / 5000f) * 255
                binding.root.setBackgroundColor(Color.argb(alpha.toInt(), 128, 128, 128))
            }


            @SuppressLint("ResourceAsColor")
            override fun onFinish() {
                binding.countdownTextview.text = "Done !"
                binding.root.setBackgroundColor(R.color.teal_700)
                binding.countdownTextview.isEnabled = true
                val callIntent = Intent(Intent.ACTION_DIAL)
                callIntent.data = Uri.parse("tel:$phoneNumber")
                startActivity(callIntent)

            }
        }.start()
    }

    override fun onStop() {
        super.onStop()
        countdownTimer?.cancel()
        countdownTimer = null
    }

    private fun onButtonClicked() {
        if (countdownTimer == null) {
            binding.buttonStop.text = "Stop"
            startCountdown()
        } else {
            binding.buttonStop.text = "I Call..."
            binding.root.setBackgroundColor(Color.parseColor("#E0CDA9"))
            onStop()
            binding.countdownTextview.text = "5"
        }
    }
}

