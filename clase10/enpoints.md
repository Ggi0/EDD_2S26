


GET /api/cantantes

GET /api/cantantes/<id>

POST /api/cantantes
```
{
    "id": 6,
    "nombre": "Shakira",
    "genero": "Pop"
}
```

DELETE /api/cantantes/<id>


POST /api/cantantes/<id>/canciones
{
    "id": 204,
    "titulo": "Around the World",
    "duracion": 429
}

GET /api/cantantes/<id>/canciones

DELETE /api/cantantes/<id>/canciones/<idCancion>

