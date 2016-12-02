<?php
if (session_status() !== PHP_SESSION_ACTIVE) {
    session_name("AdamTp2");
	session_start();
}
require_once "entetes.inc";

$message = "";

if(isset($_POST['connexion'])) {
	$message = (connecter($_POST['nom'], $_POST['prenom'], $_POST['mdp'])) ? "connexion reussi" : "identifiant ou mot de passe invalide";
}

function connecter($nom, $prenom, $mdp) {
	$fichier = fopen("users.csv", "r");
	$boolean = false;

	// on parcours chaque ligne
	while($tab = fgetcsv($fichier, 1024, ';')) {
		if(count($tab) == 3) {
			$fnom = $tab[0]; 
			$fprenom = $tab[1];
			$fmdp = $tab[2];

			if(strcmp($fnom, $nom) == 0 && strcmp($fprenom, $prenom) == 0  && strcmp($fmdp, $mdp) == 0) {
				$_SESSION['u_connecte'] = "oui";
				$_SESSION['u_nom'] = $nom;
				$_SESSION['u_prenom'] = $prenom;
				$boolean = true;
				break;
			}
		}
	}

	fclose($fichier);
	return $boolean;
}
?>
<!doctype html>
<html lang="fr">
<?php echo __getEntete(); ?>
<body>
	<div id="body">
	<p><?php echo $message; ?></p> 
	<form action="index.php" method="post">
		<fieldset>
	    <legend>Connexion</legend>
	    Nom:<br>
	    <input type="text" name="nom" placeholder="Votre nom" pattern="[A-Za-z]{3,}" list="demo" required><br>
	    Prénom:<br>
	    <input type="text" name="prenom" placeholder="Votre prénom" pattern="[A-Za-z]{3,}" list="demo" required><br>
	    Mot de passe:<br>
	    <input type="password" name="mdp" placeholder="Votre mot de passe" pattern="[A-Za-z0-9]{2,}" list="demo" required><br><br>
	    <input type="submit" name="connexion" value="Se connecter">
	    <datalist id="demo">
	    	<option value="demo">
	    </datalist>
	  </fieldset>
	</form>
	</div>
</body>
</html>