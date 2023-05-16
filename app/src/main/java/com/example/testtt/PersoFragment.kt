import android.annotation.SuppressLint
import android.app.AlertDialog
import android.content.DialogInterface
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.EditText
import androidx.fragment.app.Fragment
import androidx.navigation.fragment.findNavController
import com.example.testtt.BDInfoPerso
import com.example.testtt.databinding.FragmentPersoBinding


class PersoFragment() : Fragment() {

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

        // Récupération des donnees de la BD
        var bdRead = bdperso.readableDatabase
        var cursor = bdRead.rawQuery("SELECT * FROM MonTableau WHERE id = 1", null)
        if (cursor.moveToFirst()) {
            val contenuEnregistre1 = cursor.getString(cursor.getColumnIndex("nom"))
            val contenuEnregistre2 = cursor.getString(cursor.getColumnIndex("dob"))
            val contenuEnregistre3 = cursor.getString(cursor.getColumnIndex("difficulte"))
            val contenuEnregistre4 = cursor.getString(cursor.getColumnIndex("gs"))
            val contenuEnregistre5 = cursor.getString(cursor.getColumnIndex("ug"))

            // Mettre à jour le contenu avec le nouveau texte
            binding.textviewNom.text = contenuEnregistre1
            binding.textviewDateNaissance.text = contenuEnregistre2
            binding.textviewMaladie.text = contenuEnregistre3
            binding.textviewGs.text = contenuEnregistre4
            binding.textviewUg.text = contenuEnregistre5

        }
        cursor.close()
        bdRead.close()


        // Gestion et mise à jour de chaque rubrique
        binding.cardviewNom.setOnClickListener {
            val builder: AlertDialog.Builder = AlertDialog.Builder(requireContext())
            builder.setTitle("Modifier le contenu")
            val input = EditText(requireContext())
            input.setText(binding.textviewNom.text) // contenuActuel est le texte à modifier

            builder.setView(input)
            builder.setPositiveButton("Enregistrer",
                DialogInterface.OnClickListener { dialog, which ->
                    // Stocker dans la BD
                    val nouveauContenu: String = input.text.toString()
                    val bdWrite = bdperso.writableDatabase
                    bdWrite.execSQL("UPDATE MonTableau SET nom = '$nouveauContenu' WHERE id = 1")
                    bdWrite.close()

                    binding.textviewNom.text = nouveauContenu


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
                    // Stocker dans la BD
                    val nouveauContenu: String = input.text.toString()
                    val bdWrite = bdperso.writableDatabase
                    bdWrite.execSQL("UPDATE MonTableau SET dob = '$nouveauContenu' WHERE id = 1")
                    bdWrite.close()

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
                    // Stocker dans la BD
                    val nouveauContenu: String = input.text.toString()
                    val bdWrite = bdperso.writableDatabase
                    bdWrite.execSQL("UPDATE MonTableau SET difficulte = '$nouveauContenu' WHERE id = 1")
                    bdWrite.close()

                    binding.textviewMaladie.text = nouveauContenu
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
                    // Stocker dans la BD
                    val nouveauContenu: String = input.text.toString()
                    val bdWrite = bdperso.writableDatabase
                    bdWrite.execSQL("UPDATE MonTableau SET gs = '$nouveauContenu' WHERE id = 1")
                    bdWrite.close()

                    binding.textviewGs.text = nouveauContenu

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
                    // Stocker dans la BD
                    val nouveauContenu: String = input.text.toString()
                    val bdWrite = bdperso.writableDatabase
                    bdWrite.execSQL("UPDATE MonTableau SET ug = '$nouveauContenu' WHERE id = 1")
                    bdWrite.close()

                    binding.textviewUg.text = nouveauContenu
                })
            builder.setNegativeButton("Annuler",
                DialogInterface.OnClickListener { dialog, which -> dialog.cancel() })
            builder.show()        }

    }
}
