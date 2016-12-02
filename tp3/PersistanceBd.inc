<?php
/**
 * PHP version 5 ou plus
 *
 * @category   L3 Web Persistance
 * @package    web.tp3
 * @author     Adam Issoufi <issoufi.adam1@gmail.com>
 * @version    0.0
 * @link       http://www-mips.unice.fr/~ai401938/web/tp3
 */

require_once "__autoload.inc";
__autoload("Categorie");
__autoload("Article");

class PersistanceBd implements Persistance {
	/**
	 * Document XML, la racine de l'arbre document.
	 * @var DOMDocument
	 */
	private $bdd;

	/**
	 * Liste des catégories
	 * @var Array
	 */
	private $categories;

	/**
	 * constructeur
	 * @param string $fichier : Nom du fichier xml à charger. Par défaut news.xml
	 */
	function __construct($server, $database, $username, $password) {
		$this->categories = array();

		if ($_SERVER["SERVER_NAME"]=="localhost") {
			$server = "localhost";
			$database = "tp3";
			$username = "root";
			$password = "";
		}

		try {
			$this->bdd = new PDO("mysql:host={$server};dbname={$database};charset=utf8", $username, $password);
		} catch (Exception $e) {
			die('Erreur : ' . $e->getMessage());
		}
	}
	
	/**
	 * permet de charger toutes les catégories et tous les articles
	 *
	 * @return boolean : vrai en cas de succès, faux sinon
	 */
	public function charger() {
		$categories = $this->bdd->query('SELECT * FROM categories;');

		// On affiche chaque entrée une à une
		while ($categorie = $categories->fetch()) {
			$nom = $categorie['nom'];
			$categorie_tmp = new Categorie($nom);

			$articles = $this->bdd->query("SELECT * FROM articles WHERE `categorie`= '{$nom}' ORDER BY `articles`.`titre` ASC;");
			while ($article = $articles->fetch()) {
				$titre = $article['titre'];
				$auteur = $article['auteur'];
				$texte = $article['texte'];

				$categorie_tmp->addArticle(new Article($titre, $auteur, $texte));
			}
			$this->categories[$nom] = $categorie_tmp;
		}

		return true;
	}
	
	/**
	 * Permet de récupèrer toutes les catégories
	 *
	 * @return array : retourne un tableau de toutes les catégories lues
	 */
	public function getCategories() {
		return $this->categories;
	}
	
	/**
	 * Permet de récupèrer tous les articles
	 *
	 * @return array : retourne un tableau de tous les articles lus de toutes les catégories lues
	 */
	public function getArticles() {
		$articles = array();
		foreach($this->categories as $categorie) {
			foreach ($categorie->getArticles() as $value) {
				$articles[] = $value;
			}
		}
		return $articles;
	}

	/**
	 * Permet de récupèrer la liste de nom des catégories
	 *
	 * @return array : retourne un tableau conteanat le non de toutes les catégories
	 */
	public function getNomsCategorie() {
		return array_keys($this->categories);
	}

	/**
	 * Permet de récupèrer une catégorie
	 *
	 * @param string $nom : Le nom de la catégorie que l'on souhaite récupérer 
	 * @return array : retourne un tableau conteanat le non de toutes les catégories
	 */
	public function getCategorie($nom) {
		if($this->existe($nom)) {
			return $this->categories[$nom];
		}
	}

	/**
	 * Verifie si le nom de la catégorie est disponible (n'est pas utilisé) 
	 *
	 * @param string $nom : Le nom de la catégorie que l'on souhaite varifié la disponibilité
	 * @return boolean : retourne un true si le nom n'est pas disponible, sinon false
	 */
	public function existe($nom) {
		return key_exists($nom, $this->categories);
	}

	/**
	 * Ajoute un article dans une catégorie
	 *
	 * @param string $nomCategorie : Le nom de la catégorie que l'on souhaite varifié la disponibilité
	 * @param string $titre : Le titre de l'article
	 * @param string $auteur : L'auteur de l'article
	 * @param string $texte : Le texte de l'article. Le texte peut être du HTML
	 * @return boolean : retourne un true si l'opération esr reussie, sinon false
	 */
	public function ajouterArtcile($nomCategorie, $titre, $auteur, $texte) {
		if($this->existe($nomCategorie)) {
			return $this->categories[$nomCategorie]->addArticle(new Article(utf8_encode($titre), utf8_encode($auteur), utf8_encode($texte)));
		}
		return false;
	}

	/**
	 * Créer une nouvelle catégorie
	 *
	 * @param string $nom : Le nom de la catégorie que l'on souhaite créer
	 * @return boolean : retourne un true si l'opération esr reussie, sinon false
	 */
	public function ajouterCategorie($nom) {
		$nom = trim($nom);
		if(!$this->existe($nom)) {
			$this->categories[$nom] = new Categorie(utf8_encode($nom));
			return true;
		}
		return false;
	}

	/**
	 * Sauvgarde les modifications
	 */
	public function save() {
		$cat_query = $this->bdd->prepare("INSERT INTO `categories`(`nom`) VALUES (:nom)");

		//$art_query = $this->bdd->prepare("INSERT INTO `articles`(`categorie`, `titre`, `auteur`, `texte`) VALUES (:categorie, :titre, :auteur, :texte) WHERE NOT EXISTS (SELECT * FROM `articles` WHERE `titre` = :titre)");

		$art_query = $this->bdd->prepare("INSERT INTO `articles`(`categorie`, `titre`, `auteur`, `texte`) SELECT * FROM (SELECT :categorie, :titre, :auteur, :texte) AS tmp WHERE NOT EXISTS (SELECT * FROM `articles` WHERE `titre`=:titre and `categorie`=:categorie) LIMIT 1;");

		foreach ($this->categories as $nom_cat => $categorie) {
			$cat_query->execute(array('nom' => $nom_cat));
		}

		$articles = $this->getArticles();
		foreach ($articles as $nom_art => $article) {
			$nom_cat = $article->getCategorie()->getNom();
			$titre = $article->getTitre();
			$auteur = $article->getAuteur();
			$texte = $article->getTexte();

			$art_query->execute(array('categorie' => $nom_cat, 'titre' => $titre, 'auteur' => $auteur, 'texte' => $texte));
		}
	}	
}

?>