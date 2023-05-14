import android.annotation.SuppressLint
import android.app.AlertDialog
import android.content.ContentValues
import android.content.DialogInterface
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.EditText
import androidx.fragment.app.Fragment
import androidx.navigation.fragment.findNavController
import com.example.testtt.BDInfoPerso
import com.example.testtt.SoundFragmentDirections
import com.example.testtt.VisualFragmentDirections
import com.example.testtt.databinding.FragmentPersoBinding


class PersoFragment : Fragment() {

    private lateinit var binding: FragmentPersoBinding

    private lateinit var bdperso: BDInfoPerso


    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        binding = FragmentPersoBinding.inflate(inflater, container, false)
        bdperso = BDInfoPerso(requireContext())
        return binding.root
    }

    @SuppressLint("Range")
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
                    // Stocker dans la BD
                    val nouveauContenu: String = input.text.toString()
                    val bdWrite = bdperso.writableDatabase
                    val contentValues = ContentValues()
                    contentValues.put("nom", nouveauContenu)
                    bdWrite.insert("MonTableau", null, contentValues)
                    bdWrite.close()

                    // Recuperer de la BD
                    val bdRead = bdperso.readableDatabase
                    val cursor = bdRead.rawQuery("SELECT nom FROM MonTableau ", null)
                    if (cursor.moveToFirst()) {
                        val contenuEnregistre = cursor.getString(cursor.getColumnIndex("nom"))
                        // Mettre à jour le contenu avec le nouveau texte
                        binding.textviewNom.text = contenuEnregistre
                    }
                    cursor.close()
                    bdRead.close()

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
                    binding.textviewDateNaissance.text = nouveauContenu
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
