<?php
require_once "__autoload.inc";
__autoload("Categorie");
__autoload("Article");

class PersistanceXml implements Persistance{
	private $xml;
	private $categories;

	function __construct($fichier = "news.xml") {
		$this->xml = new DOMDocument();
		$this->xml->load($fichier);
		$this->categories = array();
	}
	
	/**
	 * permet de charger toutes les catégories et tous les articles
	 * @return boolean : vrai en cas de succès, faux sinon
	 */
	public function charger() {
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
	 * @return array retourne un tableau de toutes les catégories lues
	 */
	public function getCategories() {
		return $this->categories;
	}
	
	/**
	 * @return array retourne un tableau de toutes les articles lus de toutes les catégories lues
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

	public function getNomsCategorie() {
		return array_keys($this->categories);
	}

	public function getCategorie($nom) {
		if($this->existe($nom)) {
			return $this->categories[$nom];
		}
	}

	public function existe($nom) {
		return key_exists($nom, $this->categories);
	}

	public function ajouterArtcile($nomCategorie, $titre, $auteur, $texte) {
		if($this->existe($nomCategorie)) {
			$this->categories[$nomCategorie]->addArticle(new Article($titre, $auteur, $texte));
		}
	}

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
		$this->xml->save('news.xml');
	}

	
}
?>