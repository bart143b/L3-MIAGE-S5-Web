<?php
class Categorie {
	
	/**
	 * liste des articles
	 * @var Array
	 */
	private $articles = array();
	
	/**
	 * nom de la catégorie
	 * @var string
	 */
	private $nom;
	
	/**
	 * constructeur
	 * @param string $nom
	 */
	public function Categorie($nom = "sports")
	{
		$this->nom = $nom;
	}
	
	/**
	 * pour ajouter un article à la catégorie
	 * @param Article $a
	 */
	public function addArticle(Article $a)
	{
		if (! key_exists($a->getTitre(), $this->articles))
		{
			$this->articles[$a->getTitre()] = $a;
			$a->setCategorie($this);
			// ce n'est pas persistant
		}
	}
	
	/**
	 * pour retirer un article de la catégorie
	 * @param Article $a
	 */
	public function removeArticle(Article $a)
	{
		if (key_exists($a->getTitre(), $this->articles))
		{
			unset($this->articles[$a->getTitre()]);
			// ce n'est pas persistant
		}
	}
	
	/**
	 * pour obtenir une vue html de la catégorie
	 * @return string code html pour afficher la catégorie et ses articles
	 */
	public function getHtml()
	{
		$result = "";
		
		if ($this->articles)
		{
			$result = "<ul>\n";
			
			foreach($this->articles as $a)
			{
				$result .= "\t<li>{$a->getHtml()}</li>\n";
			}
			$result .= "</ul>\n";
			
		}
		
		return $result;
			
	}
	
	/**
	 * @return array les articles de cette catégorie
	 */
	public function getArticles()
	{
		return $this->articles;
	}
	
	public function getNom()
	{
		return $this->nom;
	}
}
?>