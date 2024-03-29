#include "shapes.h"

BasicShapeArrays::BasicShapeArrays(const GLfloat* data, GLsizeiptr byteSize)
{
    // DONE Partie 1: Générer et bind le vao de la forme.
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    // DONE Partie 1: Générer et bind le vbo de la forme.
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // Allouer l'espace nécessaire dans le mode approprié
    // et envoyer les données au gpu.
	glBufferData(GL_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW);
}

BasicShapeArrays::~BasicShapeArrays()
{
    // DONE Partie 1: Supprimer la mémoire de l'objet.
    // Assurez-vous que les ressources ne soient pas utilisées
    // pendant la suppression.
    glBindVertexArray(NULL);
    glDeleteVertexArrays(1, &m_vao);
}

void BasicShapeArrays::enableAttribute(GLuint index, GLint size, GLsizei stride, GLsizeiptr offset)
{
    // DONE Partie 1: Activer un attribut et l'attacher correctement au state du vao.
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE,stride,(void*)offset);
    glEnableVertexAttribArray(index);

}

void BasicShapeArrays::draw(GLenum mode, GLsizei count)
{
    // DONE Partie 1: Dessiner la forme.
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glDrawArrays(mode,0,count);
}



BasicShapeMultipleArrays::BasicShapeMultipleArrays(const GLfloat* pos, GLsizeiptr posByteSize, const GLfloat* color, GLsizeiptr colorByteSize)
{
    // DONE Partie 1: Générer et bind le vao de la forme.
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    // DONE Partie 1: Générer et bind les vbos (un pour la position,
    // l'autre pour la couleur) de la forme. Allouer l'espace
    // nécessaire dans le mode approprié et envoyer les données au gpu.
    glGenBuffers(1, &m_posVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_posVbo);
	glBufferData(GL_ARRAY_BUFFER, posByteSize, pos, GL_STATIC_DRAW);
    
    glGenBuffers(1, &m_colorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorVbo);
	glBufferData(GL_ARRAY_BUFFER, colorByteSize, color, GL_STATIC_DRAW);
}

BasicShapeMultipleArrays::~BasicShapeMultipleArrays()
{
    // DONE Partie 1: Supprimer la mémoire de l'objet.
    // Assurez-vous que les ressources ne soient pas utilisées
    // pendant la suppression.
    glBindVertexArray(NULL);
    glDeleteVertexArrays(1, &m_vao);
}

void BasicShapeMultipleArrays::enablePosAttribute(GLuint index, GLint size, GLsizei stride, GLsizeiptr offset)
{
    // DONE Partie 1: Activer l'attribut de position et l'attacher correctement au state du vao.
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_posVbo);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE,stride,(void*)offset);
}

void BasicShapeMultipleArrays::enableColorAttribute(GLuint index, GLint size, GLsizei stride, GLsizeiptr offset)
{
    // DONE Partie 1: Activer l'attribut de couleur et l'attacher correctement au state du vao.
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorVbo);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE,stride,(void*)offset);
}

void BasicShapeMultipleArrays::updateColorData(const GLfloat* color, GLsizeiptr colorByteSize)
{
    // DONE Partie 1: Modifier la totalité des données de couleur
    glBindBuffer(GL_ARRAY_BUFFER, m_colorVbo);
    glBufferSubData(GL_ARRAY_BUFFER,0, colorByteSize, color);
}

GLfloat* BasicShapeMultipleArrays::mapPosData()
{
    // DONE Partie 1: Activer le mapping des données de position
    glBindBuffer(GL_ARRAY_BUFFER, m_posVbo);
    return (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void BasicShapeMultipleArrays::unmapPosData()
{
    // DONE Partie 1: Désactiver le mapping des données de position
    glBindBuffer(GL_ARRAY_BUFFER, m_posVbo);
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void BasicShapeMultipleArrays::draw(GLenum mode, GLsizei count)
{
    // DONE Partie 1: Dessiner la forme.
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_posVbo);
    glDrawArrays(mode,0,count);
}


BasicShapeElements::BasicShapeElements(const GLfloat* data, GLsizeiptr byteSize, const GLubyte* indexes, GLsizeiptr indexesByteSize)
{
    // DONE Partie 1: Générer et bind le vao de la forme.
	glGenBuffers(1, &m_vao);
    // DONE Partie 1: Générer et bind le vbo et ebo de la forme.
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    // Allouer l'espace nécessaire dans le mode approprié
    // et envoyer les données au gpu.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteSize, data, GL_STATIC_DRAW);
}

BasicShapeElements::~BasicShapeElements()
{
    // DONE Partie 1: Supprimer la mémoire de l'objet.
    // Assurez-vous que les ressources ne soient pas utilisées
    // pendant la suppression.
    glBindVertexArray(NULL);
    glDeleteVertexArrays(1, &m_vao);
}

void BasicShapeElements::enableAttribute(GLuint index, GLint size, GLsizei stride, GLsizeiptr offset)
{
    // DONE Partie 1: Activer un attribut et l'attacher correctement au state du vao.
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE,stride,(void*)offset);
    glEnableVertexAttribArray(index);
}

void BasicShapeElements::draw(GLenum mode, GLsizei count)
{
    // DONE Partie 1: Dessiner la forme avec le ebo.
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glDrawElements(mode,count, GL_UNSIGNED_BYTE, 0);
}
