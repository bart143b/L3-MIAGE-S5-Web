<?php
class Bandeau {
	// valeurs possible "toujours accessible", "accessible si connecte", "accessible si deconnecte"
	public static $publicAcces = array( "connexion" => "toujours accessible",
										"plan du site" => "toujours accessible",
										"choix du style" => "accessible si connecte",
										"manipulation de dates" => "accessible si deconnecte");

	public static $map = array( array("index.php", "connexion"),
								array("tableau.php", "plan du site"),
              					array("preference.php", "choix du style"),
              					array("date.php", "manipulation de dates"));
	/**
	 * @param  [type]
	 * @param  [type]
	 * @return [type]
	 */
	function genererLien($href, $name) {
		return "<div class='lien'><a href='{$href}'>{$name}</a></div>";
	}

	/**
	 * @return [type]
	 */
	function genererBarNav($nom = "cher visiteur") {
		$nav = '<div id="header">';
		$nav .= '<div class="droite">';
		$nav .= strftime("bienvenu {$nom}, nous sommes le %d %B %Y, %H:%M:%S");
		$nav .= '</div>';
		$nav .= '<div id="barrenavigation">';
		for($i=0; $i<count(Bandeau::$map); $i++) {
			$access = Bandeau::$publicAcces[Bandeau::$map[$i][1]];
			switch ($access) {
				case 'accessible si connecte':
					if(strcmp($nom, "cher visiteur") != 0)
						$nav .= $this->genererLien(dirname($_SERVER['PHP_SELF'])."/".Bandeau::$map[$i][0], Bandeau::$map[$i][1]);
					break;
				case 'accessible si deconnecte':
					if(strcmp($nom, "cher visiteur") == 0)
						$nav .= $this->genererLien(dirname($_SERVER['PHP_SELF'])."/".Bandeau::$map[$i][0], Bandeau::$map[$i][1]);
					break;
				default:
					$nav .= $this->genererLien(dirname($_SERVER['PHP_SELF'])."/".Bandeau::$map[$i][0], Bandeau::$map[$i][1]);
					break;
			}
		}
		$nav .= '</div></div>';
		return $nav;
	}

}


?>