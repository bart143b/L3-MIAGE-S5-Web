<?php
/**
 * PHP version 5 ou plus
 *
 * @category   L3 Web Persistance
 * @package    web.tp3
 * @author     Adam Issoufi <issoufi.adam1@gmail.com>
 * @version    1.0
 * @link       http://www-mips.unice.fr/~ai401938/web/tp3
 */

require_once "__autoload.inc";
__autoload("Categorie");
__autoload("Article");

class PersistanceXml implements Persistance{

	/**
	 * Document XML, la racine de l'arbre document.
	 * @var DOMDocument
	 */
	private $xml;

	/**
	 * Liste des catégories
	 * @var Array
	 */
	private $categories;

	/**
	 * Nom du fichier xml chargée
	 * @var String
	 */
	private $nomFichierXml;

	/**
	 * constructeur
	 * @param string $fichier : Nom du fichier xml à charger. Par défaut news.xml
	 */
	function __construct($fichier = "news.xml") {
		$this->xml = new DOMDocument();
		$this->xml->load($fichier);
		$this->categories = array();
		$this->nomFichierXml = $fichier;
	}
	
	/**
	 * permet de charger toutes les catégories et tous les articles
	 *
	 * @return boolean : vrai en cas de succès, faux sinon
	 */
	public function charger() {
		if(!$this->xml->validate()) return false;

		$categories = $this->xml->getElementsByTagName('categorie');

		foreach($categories as $categorie) {
			$nom = $categorie->getElementsByTagName('nom')->item(0)->nodeValue;
			$categorie_tmp = new Categorie($nom);

			$articles = $categorie->getElementsByTagName('article');
			foreach($articles as $article) {
				$titre = $article->getElementsByTagName('titre')->item(0)->nodeValue;
				$auteur = $article->getElementsByTagName('auteur')->item(0)->nodeValue;
				$texte = $article->getElementsByTagName('texte')->item(0)->nodeValue;

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
		$this->xml->formatOutput = true;
		$tag_ancien_news = $this->xml->getElementsByTagName("news")->item(0);
		$tag_news = $this->xml->createElement('news');
		foreach ($this->categories as $nom_cat => $categorie) {
			$tag_cat = $this->xml->createElement('categorie');
			$nom = $this->xml->createElement('nom', $nom_cat);

			$tag_cat->appendChild($nom);

			$articles = $categorie-> getArticles();
			foreach ($articles as $nom_art => $article) {
				$tag_art = $this->xml->createElement('article');

				$titre = $this->xml->createElement('titre');
				$titre_c = $this->xml->createCDATASection($article->getTitre());

				$auteur = $this->xml->createElement('auteur');
				$auteur_c = $this->xml->createCDATASection($article->getAuteur());

				$texte = $this->xml->createElement('texte');
				$texte_c = $this->xml->createCDATASection($article->getTexte());

				$titre->appendChild($titre_c);
				$auteur->appendChild($auteur_c);
				$texte->appendChild($texte_c);

				$tag_art->appendChild($titre);
				$tag_art->appendChild($auteur);
				$tag_art->appendChild($texte);
				
				$tag_cat->appendChild($tag_art);
			}
			$tag_news->appendChild($tag_cat);
		}
		$this->xml->replaceChild($tag_news, $tag_ancien_news);
		$this->xml->save($this->nomFichierXml);
	}	
}
?>