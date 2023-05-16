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
    fun retourDef(valeur1: Int,valeur2: Int,valeur3: Int,valeur4: Int,valeur5: Int,valeur6: Int,valeur7: Int,valeur8: Int){
        if(valeur1< DANGER_ZONE){
            binding.capteur1.setColorFilter(resources.getColor(R.color.red), PorterDuff.Mode.MULTIPLY) }
        if(valeur1 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur1.setColorFilter( resources.getColor(R.color.yellow),PorterDuff.Mode.MULTIPLY)}
        if(valeur1 > WARNING_ZONE){
            binding.capteur1.setColorFilter(resources.getColor(R.color.green), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur2< DANGER_ZONE){
            binding.capteur2.setColorFilter(resources.getColor(R.color.red), PorterDuff.Mode.MULTIPLY) }
        if(valeur2 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur2.setColorFilter( resources.getColor(R.color.yellow),PorterDuff.Mode.MULTIPLY)}
        if(valeur2 > WARNING_ZONE){
            binding.capteur2.setColorFilter(resources.getColor(R.color.green), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur3< DANGER_ZONE){
            binding.capteur3.setColorFilter(resources.getColor(R.color.red), PorterDuff.Mode.MULTIPLY) }
        if(valeur3 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur3.setColorFilter( resources.getColor(R.color.yellow),PorterDuff.Mode.MULTIPLY)}
        if(valeur3 > WARNING_ZONE){
            binding.capteur3.setColorFilter(resources.getColor(R.color.green), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur4< DANGER_ZONE){
            binding.capteur4.setColorFilter(resources.getColor(R.color.red), PorterDuff.Mode.MULTIPLY) }
        if(valeur4 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur4.setColorFilter( resources.getColor(R.color.yellow),PorterDuff.Mode.MULTIPLY)}
        if(valeur4 > WARNING_ZONE){
            binding.capteur4.setColorFilter(resources.getColor(R.color.green), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur5< DANGER_ZONE){
            binding.capteur5.setColorFilter(resources.getColor(R.color.red), PorterDuff.Mode.MULTIPLY) }
        if(valeur5 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur5.setColorFilter( resources.getColor(R.color.yellow),PorterDuff.Mode.MULTIPLY)}
        if(valeur5 > WARNING_ZONE){
            binding.capteur5.setColorFilter(resources.getColor(R.color.green), PorterDuff.Mode.MULTIPLY)
        }

        if(valeur6< DANGER_ZONE){
            binding.capteur6.setColorFilter(resources.getColor(R.color.red), PorterDuff.Mode.MULTIPLY) }
        if(valeur6 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur6.setColorFilter( resources.getColor(R.color.yellow),PorterDuff.Mode.MULTIPLY)}
        if(valeur6 > WARNING_ZONE){
            binding.capteur6.setColorFilter(resources.getColor(R.color.green), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur7< DANGER_ZONE){
            binding.capteur7.setColorFilter(resources.getColor(R.color.red), PorterDuff.Mode.MULTIPLY) }
        if(valeur7 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur7.setColorFilter( resources.getColor(R.color.yellow),PorterDuff.Mode.MULTIPLY)}
        if(valeur7 > WARNING_ZONE){
            binding.capteur7.setColorFilter(resources.getColor(R.color.green), PorterDuff.Mode.MULTIPLY)
        }

        if(valeur8< DANGER_ZONE){
            binding.capteur8.setColorFilter(resources.getColor(R.color.red), PorterDuff.Mode.MULTIPLY) }
        if(valeur8 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur8.setColorFilter( resources.getColor(R.color.yellow),PorterDuff.Mode.MULTIPLY)}
        if(valeur8 > WARNING_ZONE){
            binding.capteur8.setColorFilter(resources.getColor(R.color.green), PorterDuff.Mode.MULTIPLY)
        }
    }

    // fct pour deuteranopia
    fun retourDeut(valeur1: Int,valeur2: Int,valeur3: Int,valeur4: Int,valeur5: Int,valeur6: Int,valeur7: Int,valeur8: Int){
        if(valeur1< DANGER_ZONE){
            binding.capteur1.setColorFilter(resources.getColor(R.color.deut_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur1 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur1.setColorFilter( resources.getColor(R.color.deut_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur1 > WARNING_ZONE){
            binding.capteur1.setColorFilter(resources.getColor(R.color.deut_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur2< DANGER_ZONE){
            binding.capteur2.setColorFilter(resources.getColor(R.color.deut_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur2 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur2.setColorFilter( resources.getColor(R.color.deut_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur2 > WARNING_ZONE){
            binding.capteur2.setColorFilter(resources.getColor(R.color.deut_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur3< DANGER_ZONE){
            binding.capteur3.setColorFilter(resources.getColor(R.color.deut_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur3 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur3.setColorFilter( resources.getColor(R.color.deut_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur3 > WARNING_ZONE){
            binding.capteur3.setColorFilter(resources.getColor(R.color.deut_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur4< DANGER_ZONE){
            binding.capteur4.setColorFilter(resources.getColor(R.color.deut_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur4 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur4.setColorFilter( resources.getColor(R.color.deut_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur4 > WARNING_ZONE){
            binding.capteur4.setColorFilter(resources.getColor(R.color.deut_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur5< DANGER_ZONE){
            binding.capteur5.setColorFilter(resources.getColor(R.color.deut_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur5 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur5.setColorFilter( resources.getColor(R.color.deut_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur5 > WARNING_ZONE){
            binding.capteur5.setColorFilter(resources.getColor(R.color.deut_far), PorterDuff.Mode.MULTIPLY)
        }

        if(valeur6< DANGER_ZONE){
            binding.capteur6.setColorFilter(resources.getColor(R.color.deut_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur6 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur6.setColorFilter( resources.getColor(R.color.deut_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur6 > WARNING_ZONE){
            binding.capteur6.setColorFilter(resources.getColor(R.color.deut_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur7< DANGER_ZONE){
            binding.capteur7.setColorFilter(resources.getColor(R.color.deut_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur7 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur7.setColorFilter( resources.getColor(R.color.deut_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur7 > WARNING_ZONE){
            binding.capteur7.setColorFilter(resources.getColor(R.color.deut_far), PorterDuff.Mode.MULTIPLY)
        }

        if(valeur8< DANGER_ZONE){
            binding.capteur8.setColorFilter(resources.getColor(R.color.deut_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur8 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur8.setColorFilter( resources.getColor(R.color.deut_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur8 > WARNING_ZONE){
            binding.capteur8.setColorFilter(resources.getColor(R.color.deut_far), PorterDuff.Mode.MULTIPLY)
        }
    }


    //fct pour tritanopia
    fun retourTri(valeur1: Int,valeur2: Int,valeur3: Int,valeur4: Int,valeur5: Int,valeur6: Int,valeur7: Int,valeur8: Int){
        if(valeur1< DANGER_ZONE){
            binding.capteur1.setColorFilter(resources.getColor(R.color.tri_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur1 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur1.setColorFilter( resources.getColor(R.color.tri_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur1 > WARNING_ZONE){
            binding.capteur1.setColorFilter(resources.getColor(R.color.tri_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur2< DANGER_ZONE){
            binding.capteur2.setColorFilter(resources.getColor(R.color.tri_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur2 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur2.setColorFilter( resources.getColor(R.color.tri_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur2 > WARNING_ZONE){
            binding.capteur2.setColorFilter(resources.getColor(R.color.tri_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur3< DANGER_ZONE){
            binding.capteur3.setColorFilter(resources.getColor(R.color.tri_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur3 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur3.setColorFilter( resources.getColor(R.color.tri_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur3 > WARNING_ZONE){
            binding.capteur3.setColorFilter(resources.getColor(R.color.tri_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur4< DANGER_ZONE){
            binding.capteur4.setColorFilter(resources.getColor(R.color.tri_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur4 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur4.setColorFilter( resources.getColor(R.color.tri_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur4 > WARNING_ZONE){
            binding.capteur4.setColorFilter(resources.getColor(R.color.tri_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur5< DANGER_ZONE){
            binding.capteur5.setColorFilter(resources.getColor(R.color.tri_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur5 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur5.setColorFilter( resources.getColor(R.color.tri_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur5 > WARNING_ZONE){
            binding.capteur5.setColorFilter(resources.getColor(R.color.tri_far), PorterDuff.Mode.MULTIPLY)
        }

        if(valeur6< DANGER_ZONE){
            binding.capteur6.setColorFilter(resources.getColor(R.color.tri_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur6 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur6.setColorFilter( resources.getColor(R.color.tri_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur6 > WARNING_ZONE){
            binding.capteur6.setColorFilter(resources.getColor(R.color.tri_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur7< DANGER_ZONE){
            binding.capteur7.setColorFilter(resources.getColor(R.color.tri_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur7 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur7.setColorFilter( resources.getColor(R.color.tri_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur7 > WARNING_ZONE){
            binding.capteur7.setColorFilter(resources.getColor(R.color.tri_far), PorterDuff.Mode.MULTIPLY)
        }

        if(valeur8< DANGER_ZONE){
            binding.capteur8.setColorFilter(resources.getColor(R.color.tri_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur8 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur8.setColorFilter( resources.getColor(R.color.tri_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur8 > WARNING_ZONE){
            binding.capteur8.setColorFilter(resources.getColor(R.color.tri_far), PorterDuff.Mode.MULTIPLY)
        }
    }

    //fct pour protanopia
    fun retourPro(valeur1: Int,valeur2: Int,valeur3: Int,valeur4: Int,valeur5: Int,valeur6: Int,valeur7: Int,valeur8: Int){
        if(valeur1< DANGER_ZONE){
            binding.capteur1.setColorFilter(resources.getColor(R.color.prota_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur1 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur1.setColorFilter( resources.getColor(R.color.prota_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur1 > WARNING_ZONE){
            binding.capteur1.setColorFilter(resources.getColor(R.color.prota_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur2< DANGER_ZONE){
            binding.capteur2.setColorFilter(resources.getColor(R.color.prota_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur2 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur2.setColorFilter( resources.getColor(R.color.prota_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur2 > WARNING_ZONE){
            binding.capteur2.setColorFilter(resources.getColor(R.color.prota_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur3< DANGER_ZONE){
            binding.capteur3.setColorFilter(resources.getColor(R.color.prota_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur3 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur3.setColorFilter( resources.getColor(R.color.prota_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur3 > WARNING_ZONE){
            binding.capteur3.setColorFilter(resources.getColor(R.color.prota_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur4< DANGER_ZONE){
            binding.capteur4.setColorFilter(resources.getColor(R.color.prota_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur4 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur4.setColorFilter( resources.getColor(R.color.prota_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur4 > WARNING_ZONE){
            binding.capteur4.setColorFilter(resources.getColor(R.color.prota_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur5< DANGER_ZONE){
            binding.capteur5.setColorFilter(resources.getColor(R.color.prota_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur5 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur5.setColorFilter( resources.getColor(R.color.prota_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur5 > WARNING_ZONE){
            binding.capteur5.setColorFilter(resources.getColor(R.color.prota_far), PorterDuff.Mode.MULTIPLY)
        }

        if(valeur6< DANGER_ZONE){
            binding.capteur6.setColorFilter(resources.getColor(R.color.prota_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur6 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur6.setColorFilter( resources.getColor(R.color.prota_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur6 > WARNING_ZONE){
            binding.capteur6.setColorFilter(resources.getColor(R.color.prota_far), PorterDuff.Mode.MULTIPLY)
        }


        if(valeur7< DANGER_ZONE){
            binding.capteur7.setColorFilter(resources.getColor(R.color.prota_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur7 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur7.setColorFilter( resources.getColor(R.color.prota_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur7 > WARNING_ZONE){
            binding.capteur7.setColorFilter(resources.getColor(R.color.prota_far), PorterDuff.Mode.MULTIPLY)
        }

        if(valeur8< DANGER_ZONE){
            binding.capteur8.setColorFilter(resources.getColor(R.color.prota_close), PorterDuff.Mode.MULTIPLY) }
        if(valeur8 in DANGER_ZONE.. WARNING_ZONE){
            binding.capteur8.setColorFilter( resources.getColor(R.color.prota_next),PorterDuff.Mode.MULTIPLY)}
        if(valeur8 > WARNING_ZONE){
            binding.capteur8.setColorFilter(resources.getColor(R.color.prota_far), PorterDuff.Mode.MULTIPLY)
        }
    }





    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        binding.backButton.setOnClickListener{
            val action = VisualFragmentDirections.actionVisualFragmentToHomepageFragment()
            findNavController().navigate(action)
        }



        // Runnable pour afficher la distance quand la valeur change
        val delay = 2000L // 2 secondes
        val handler = Handler(Looper.getMainLooper())


        //par defaut
        val runnable = object : Runnable {
            val capteur = arrayOf(intArrayOf(90,90,90,90,90,45,34,24,11,4,38,49,68,90,90,90,90,90,90,90,90,90,90,90,90), intArrayOf(91,90,59,45,36,29,12,35,40,69,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90), intArrayOf(92,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90),intArrayOf(93,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90),intArrayOf(94,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,45,36,20,10,17,34,69),intArrayOf(95,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,35,34,27,12,19,49,68,90,90),intArrayOf(96,90,90,90,90,90,90,90,90,90,90,90,90,90,50,34,29,12,12,36,90,90,90,90,90,),intArrayOf(97,90,90,90,90,90,90,90,46,12,25,34,56,94,90,90,90,90,90,90,90,90,90,90,90))
            var i=0
            var j=0
            var k=0
            var l=0
            var m=0
            var n=0
            var p=0
            var q=0
            override fun run() {
                retourDef(capteur[0][i],capteur[1][j],capteur[2][k],capteur[3][l],capteur[4][m],capteur[5][n],capteur[6][p],capteur[7][q])
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

                // post the runnable again after 2 seconds
                handler.postDelayed(this, delay)
            }

        }
        // start the runnable
        handler.postDelayed(runnable, delay)

        //quand boutton defaut
        val runnable1 = object : Runnable {
            val capteur = arrayOf(intArrayOf(90,90,90,90,90,45,34,24,11,4,38,49,68,90,90,90,90,90,90,90,90,90,90,90,90), intArrayOf(91,90,59,45,36,29,12,35,40,69,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90), intArrayOf(92,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90),intArrayOf(93,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90),intArrayOf(94,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,45,36,20,10,17,34,69),intArrayOf(95,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,35,34,27,12,19,49,68,90,90),intArrayOf(96,90,90,90,90,90,90,90,90,90,90,90,90,90,50,34,29,12,12,36,90,90,90,90,90,),intArrayOf(97,90,90,90,90,90,90,90,46,12,25,34,56,94,90,90,90,90,90,90,90,90,90,90,90))
            var i=0
            var j=0
            var k=0
            var l=0
            var m=0
            var n=0
            var p=0
            var q=0
            override fun run() {
                retourDef(capteur[0][i],capteur[1][j],capteur[2][k],capteur[3][l],capteur[4][m],capteur[5][n],capteur[6][p],capteur[7][q])
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
                // post the runnable again after 2 seconds
                handler.postDelayed(this, delay)
            }
        }

        //quand boutton deut
        val runnable2 = object : Runnable {
            val capteur = arrayOf(intArrayOf(90,90,90,90,90,45,34,24,11,4,38,49,68,90,90,90,90,90,90,90,90,90,90,90,90), intArrayOf(91,90,59,45,36,29,12,35,40,69,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90), intArrayOf(92,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90),intArrayOf(93,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90),intArrayOf(94,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,45,36,20,10,17,34,69),intArrayOf(95,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,35,34,27,12,19,49,68,90,90),intArrayOf(96,90,90,90,90,90,90,90,90,90,90,90,90,90,50,34,29,12,12,36,90,90,90,90,90,),intArrayOf(97,90,90,90,90,90,90,90,46,12,25,34,56,94,90,90,90,90,90,90,90,90,90,90,90))
            var i=0
            var j=0
            var k=0
            var l=0
            var m=0
            var n=0
            var p=0
            var q=0
            override fun run() {
                retourDeut(capteur[0][i],capteur[1][j],capteur[2][k],capteur[3][l],capteur[4][m],capteur[5][n],capteur[6][p],capteur[7][q])
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
                // post the runnable again after 2 seconds
                handler.postDelayed(this, delay)
            }
        }

        //qaund boutton pro
        val runnable3 = object : Runnable {
            val capteur = arrayOf(intArrayOf(90,90,90,90,90,45,34,24,11,4,38,49,68,90,90,90,90,90,90,90,90,90,90,90,90), intArrayOf(91,90,59,45,36,29,12,35,40,69,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90), intArrayOf(92,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90),intArrayOf(93,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90),intArrayOf(94,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,45,36,20,10,17,34,69),intArrayOf(95,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,35,34,27,12,19,49,68,90,90),intArrayOf(96,90,90,90,90,90,90,90,90,90,90,90,90,90,50,34,29,12,12,36,90,90,90,90,90,),intArrayOf(97,90,90,90,90,90,90,90,46,12,25,34,56,94,90,90,90,90,90,90,90,90,90,90,90))
            var i=0
            var j=0
            var k=0
            var l=0
            var m=0
            var n=0
            var p=0
            var q=0
            override fun run() {
                retourPro(capteur[0][i],capteur[1][j],capteur[2][k],capteur[3][l],capteur[4][m],capteur[5][n],capteur[6][p],capteur[7][q])
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
                // post the runnable again after 2 seconds
                handler.postDelayed(this, delay)
            }
        }


        //quand boutton tri
        val runnable4 = object : Runnable {
            val capteur = arrayOf(intArrayOf(90,90,90,90,90,45,34,24,11,4,38,49,68,90,90,90,90,90,90,90,90,90,90,90,90), intArrayOf(91,90,59,45,36,29,12,35,40,69,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90), intArrayOf(92,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90),intArrayOf(93,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90),intArrayOf(94,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,45,36,20,10,17,34,69),intArrayOf(95,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,35,34,27,12,19,49,68,90,90),intArrayOf(96,90,90,90,90,90,90,90,90,90,90,90,90,90,50,34,29,12,12,36,90,90,90,90,90,),intArrayOf(97,90,90,90,90,90,90,90,46,12,25,34,56,94,90,90,90,90,90,90,90,90,90,90,90))
            var i=0
            var j=0
            var k=0
            var l=0
            var m=0
            var n=0
            var p=0
            var q=0
            override fun run() {
                retourTri(capteur[0][i],capteur[1][j],capteur[2][k],capteur[3][l],capteur[4][m],capteur[5][n],capteur[6][p],capteur[7][q])
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
                // post the runnable again after 2 seconds
                handler.postDelayed(this, delay)
            }
        }





        binding.setting.setOnClickListener {

            // Créer une AlertDialog pour afficher le bouton on/off
            val dialogBuilder = AlertDialog.Builder(requireContext())
            dialogBuilder.setTitle(getString(R.string.opt))
            val switchView = layoutInflater.inflate(R.layout.fragment_visual_option, null)
            dialogBuilder.setView(switchView)
            val toggleSwitch = switchView.findViewById<Switch>(R.id.toggleSwitchSo)
            val RBdefaut = switchView.findViewById<RadioButton>(R.id.radioButtonD)
            val RBprotanopia = switchView.findViewById<RadioButton>(R.id.radioButtonPro)
            val RBdeuteranopia = switchView.findViewById<RadioButton>(R.id.radioButtonDeut)
            val RBtritanopia = switchView.findViewById<RadioButton>(R.id.radioButtonTri)



            dialogBuilder.setPositiveButton("OK") { _, _ ->

                //coche des palettes

                if (RBdefaut.isChecked) {
                    binding.far.background.setTint(resources.getColor(R.color.green))
                    binding.middle.background.setTint(resources.getColor(R.color.yellow))
                    binding.close.background.setTint(resources.getColor(R.color.red))


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
                    binding.close.background.setTint(resources.getColor(R.color.tri_close))


                    // start the runnable
                    handler.postDelayed(runnable4, delay)

                    //stop les autres runnable
                    handler.removeCallbacks(runnable)
                    handler.removeCallbacks(runnable1)
                    handler.removeCallbacks(runnable2)
                    handler.removeCallbacks(runnable3)
                }



                if (toggleSwitch.isChecked) {
                    findNavController().navigate(R.id.soundAndVisualFragment)
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
