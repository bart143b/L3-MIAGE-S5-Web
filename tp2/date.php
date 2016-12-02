<?php 
if (session_status() !== PHP_SESSION_ACTIVE) {
    session_name("AdamTp2");
	session_start();
}

require_once "entetes.inc";

setlocale(LC_TIME, 'fr', 'fr_FR', 'fr_FR.utf-8');

//$nom_jour_fr = array("dimanche", "lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi");
//$mois_fr = Array("", "janvier", "février", "mars", "avril", "mai", "juin", "juillet", "août", "septembre", "octobre", "novembre", "décembre");

$dateAjrd = date("Y/m/d H:i:s");
$dateSaisi = (isset($_GET['date_saisi'])) ? date($_GET['date_saisi']) : date("2016/11/01");

$timestampAjrd = strtotime($dateAjrd);
$timestampSaisi = strtotime($dateSaisi);
$timestampNbJours = ($timestampAjrd >= $timestampSaisi) ? $timestampAjrd-$timestampSaisi : $timestampSaisi-$timestampAjrd;

$nbJours = $timestampNbJours/(60*60*24);
$nbSecondes = ($nbJours-(int)$nbJours)*24*60*60;

$horodate = strftime("Nous sommes le %A %d %B %Y et il est %H:%M.", $timestampAjrd);
$texte = "Il y'a ".(int)$nbJours." jours et {$nbSecondes} secondes entre ".strftime("le %d %B %Y", $timestampAjrd).strftime(" et le %d %B %Y", $timestampSaisi);
?>
<!doctype html>
<html lang="fr">
<?php echo __getEntete(); ?>
<body>
	<div id="body">
	<p><?php echo $horodate; ?></p>
	<p><?php echo $texte; ?></p>
	<hr>
	<form action="date.php" method="get">
		<p>Entrez une date <input type="text" name="date_saisi" placeholder="AAAA/MM/JJ"></p>
		<input type="submit" value="Valider">
	</form>
	</div>
</body>
</html>