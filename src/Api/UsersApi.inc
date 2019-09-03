<?php

declare(strict_types=1);

namespace SmashcastApi\Api;


use GuzzleHttp\Exception\GuzzleException;
use Psr\Http\Message\ResponseInterface;

class UsersApi extends AbstractApiBase
{
    /**
     * @throws GuzzleException
     */
    public function getUserByAccessToken(string $accessToken): ResponseInterface
    {
        return $this->apiGet('userfromtoken', ['authToken' => $accessToken]);
    }
}
