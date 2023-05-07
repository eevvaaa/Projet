import android.app.AlertDialog
import android.content.DialogInterface
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.EditText
import androidx.fragment.app.Fragment
import androidx.navigation.fragment.findNavController
import com.example.testtt.SoundFragmentDirections
import com.example.testtt.VisualFragmentDirections
import com.example.testtt.databinding.FragmentPersoBinding


class PersoFragment : Fragment() {

    private lateinit var binding: FragmentPersoBinding

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        binding = FragmentPersoBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        binding.backButton.setOnClickListener{
            val action = PersoFragmentDirections.actionPersoFragmentToHomepageFragment3()
            findNavController().navigate(action)
        }

        binding.backButtonToSound.setOnClickListener {
            val action = PersoFragmentDirections.actionPersoFragmentToSoundFragment() 
            findNavController().navigate(action)
        }

        binding.backButtonToVisual.setOnClickListener {
            val action = PersoFragmentDirections.actionPersoFragmentToVisualFragment()  
            findNavController().navigate(action)
        }
        
        binding.cardviewNom.setOnClickListener {
            val builder: AlertDialog.Builder = AlertDialog.Builder(context)
            builder.setTitle("Modifier le contenu")
            val input = EditText(context)
            input.setText(binding.textviewNom.text) // contenuActuel est le texte à modifier

            builder.setView(input)
            builder.setPositiveButton("Enregistrer",
                DialogInterface.OnClickListener { dialog, which ->
                    val nouveauContenu: String = input.getText().toString()
                    // Mettre à jour le contenu avec le nouveau texte
                    binding.textviewNom.setText(nouveauContenu)
                })
            builder.setNegativeButton("Annuler",
                DialogInterface.OnClickListener { dialog, which -> dialog.cancel() })
            builder.show()
        }

        binding.cardviewDateNaissance.setOnClickListener {
            val builder: AlertDialog.Builder = AlertDialog.Builder(context)
            builder.setTitle("Modifier le contenu")
            val input = EditText(context)
            input.setText(binding.textviewDateNaissance.text) // contenuActuel est le texte à modifier

            builder.setView(input)
            builder.setPositiveButton("Enregistrer",
                DialogInterface.OnClickListener { dialog, which ->
                    val nouveauContenu: String = input.getText().toString()
                    // Mettre à jour le contenu avec le nouveau texte
                    binding.textviewDateNaissance.setText(nouveauContenu)
                })
            builder.setNegativeButton("Annuler",
                DialogInterface.OnClickListener { dialog, which -> dialog.cancel() })
            builder.show()
        }

        binding.cardviewMaladie.setOnClickListener {
            val builder: AlertDialog.Builder = AlertDialog.Builder(context)
            builder.setTitle("Modifier le contenu")
            val input = EditText(context)
            input.setText(binding.textviewMaladie.text) // contenuActuel est le texte à modifier

            builder.setView(input)
            builder.setPositiveButton("Enregistrer",
                DialogInterface.OnClickListener { dialog, which ->
                    val nouveauContenu: String = input.getText().toString()
                    // Mettre à jour le contenu avec le nouveau texte
                    binding.textviewNom.setText(nouveauContenu)
                })
            builder.setNegativeButton("Annuler",
                DialogInterface.OnClickListener { dialog, which -> dialog.cancel() })
            builder.show()        }

        binding.cardviewGroupeSanguin.setOnClickListener {
            val builder: AlertDialog.Builder = AlertDialog.Builder(context)
            builder.setTitle("Modifier le contenu")
            val input = EditText(context)
            input.setText(binding.textviewGs.text) // contenuActuel est le texte à modifier

            builder.setView(input)
            builder.setPositiveButton("Enregistrer",
                DialogInterface.OnClickListener { dialog, which ->
                    val nouveauContenu: String = input.getText().toString()
                    // Mettre à jour le contenu avec le nouveau texte
                    binding.textviewNom.setText(nouveauContenu)
                })
            builder.setNegativeButton("Annuler",
                DialogInterface.OnClickListener { dialog, which -> dialog.cancel() })
            builder.show()        }

        binding.cardviewNumeroUrgence.setOnClickListener {
            val builder: AlertDialog.Builder = AlertDialog.Builder(context)
            builder.setTitle("Modifier le contenu")
            val input = EditText(context)
            input.setText(binding.textviewUg.text) // contenuActuel est le texte à modifier

            builder.setView(input)
            builder.setPositiveButton("Enregistrer",
                DialogInterface.OnClickListener { dialog, which ->
                    val nouveauContenu: String = input.getText().toString()
                    // Mettre à jour le contenu avec le nouveau texte
                    binding.textviewNom.setText(nouveauContenu)
                })
            builder.setNegativeButton("Annuler",
                DialogInterface.OnClickListener { dialog, which -> dialog.cancel() })
            builder.show()        }

    }

//    fun modifyItems(contenu : String){
//        val builder: AlertDialog.Builder = AlertDialog.Builder(context)
//        builder.setTitle("Modifier le contenu")
//        val input = EditText(context)
//        input.setText(contenu) // contenuActuel est le texte à modifier
//
//        builder.setView(input)
//        builder.setPositiveButton("Enregistrer",
//            DialogInterface.OnClickListener { dialog, which ->
//                val nouveauContenu: String = input.getText().toString()
//                // Mettre à jour le contenu avec le nouveau texte
//                binding.textviewNom.setText(nouveauContenu)
//            })
//        builder.setNegativeButton("Annuler",
//            DialogInterface.OnClickListener { dialog, which -> dialog.cancel() })
//        builder.show()
//    }
//
}
